#include <tuple>
#include <map>
#include <iostream>

// sequence for
template <typename T, T... S, typename F>
constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
    using unpack_t = int[];
    (void)unpack_t {
        (static_cast<void>(f(std::integral_constant<T, S>{})), 0)..., 0
    };
}

// Sample implementation of a json-like data structure. It is only there for the example to compile and actually produce a testable output
namespace Json {
    struct Value;

    struct ValueData {
        std::map<std::string, Value> subObject;
        std::string string;
        int number = 0;
    };

    struct Value {
        ValueData data;

        Value& operator[](std::string name) {
            return data.subObject[std::move(name)];
        }

        const Value& operator[](const std::string& name) const {
	        const auto it = data.subObject.find(name);

            if (it != data.subObject.end()) {
                return it->second;
            }

            throw;
        }

        Value& operator=(std::string value) {
            data.string = value;
            return *this;
        }

        Value& operator=(double value) {
            data.number = value;
            return *this;
        }
    };

    template<typename T> T& asAny(Value&);
    template<typename T> const T& asAny(const Value&);

    template<>
    int& asAny<int>(Value& value) {
        return value.data.number;
    }

    template<>
    const int& asAny<int>(const Value& value) {
        return value.data.number;
    }

    template<>
    const std::string& asAny<std::string>(const Value& value) {
        return value.data.string;
    }

    template<>
    std::string& asAny<std::string>(Value& value) {
        return value.data.string;
    }
}

template<typename Class, typename T>
struct PropertyImpl {
    constexpr PropertyImpl(T Class::* aMember, const char* aName) : member{ aMember }, name{ aName } {}

    using Type = T;

    T Class::* member;
    const char* name;
};

// One could overload this function to accept both a getter and a setter instead of a member.
template<typename Class, typename T>
constexpr auto property(T Class::* member, const char* name) {
    return PropertyImpl<Class, T>{member, name};
}


// unserialize function
template<typename T>
T fromJson(const Json::Value& data) {
    T object;

    // We first get the number of properties
    constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;

    // We iterate on the index sequence of size `nbProperties`
    for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
        // get the property
        constexpr auto property = std::get<i>(T::properties);

        // get the type of the property
        using Type = typename decltype(property)::Type;

        // set the value to the member
        object.*(property.member) = Json::asAny<Type>(data[property.name]);
        });

    return object;
}

template<typename T>
Json::Value toJson(const T& object) {
    Json::Value data;

    // We first get the number of properties
    constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;

    // We iterate on the index sequence of size `nbProperties`
    for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i) {
        // get the property
        constexpr auto property = std::get<i>(T::properties);

        // set the value to the member
        data[property.name] = object.*(property.member);
        });

    return data;
}

namespace model {

    struct session {
	    std::string name;
	    std::string time;
        std::string duration;
        std::string directedBy;
        int cost = 0;
        int count = 0;
    	
        bool operator==(const session& session) const {
            return name == session.name
                && time == session.time
        	   	&& duration == session.duration
        		&& directedBy == session.directedBy
        		&& cost == session.cost
        		&& count == session.count;
        }

        constexpr static auto properties = std::make_tuple(
            property(&session::name, "name"),
            property(&session::time, "time"),
            property(&session::duration, "duration"),
            property(&session::directedBy, "directedBy"),
            property(&session::cost, "cost"),
            property(&session::count, "count")
        );
    };

}

int main() {

    model::session session;

    // Access attributes and set values
    session.name = "Pulp Fiction";
    session.time = "Some text";
    session.duration = "154";
    session.directedBy = "Quentin Tarantino";
    session.cost = 10;
    session.count = 50;

    Json::Value json = toJson(session); // produces json

    FILE* file;
    fopen_s(&file, "session.dat", "w+");
    if (file == nullptr)
    {
        return 1;
    }

    fprintf_s(file, "%s", json.data.subObject);
    //fscanf_s(file, "%s", j);
	fclose(file);


	
    auto session2 = fromJson<model::session>(json);

    std::cout << std::boolalpha << (session == session2) << std::endl; // pass the test, both object are equal!

    return 0;
}