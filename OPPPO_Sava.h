#ifndef WISDOM_CONTAINER_H
#define WISDOM_CONTAINER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Wisdom {
public:
    std::string content;

    Wisdom(const std::string& c) : content(c) {}

    virtual std::string getType() const = 0;
    virtual bool matchesCondition(const std::string& condition) const = 0;

    virtual ~Wisdom() = default;
};

class Aphorism : public Wisdom {
public:
    std::string author;

    Aphorism(const std::string& c, const std::string& a) : Wisdom(c), author(a) {}

    std::string getType() const override {
        return "Aphorism";
    }

    bool matchesCondition(const std::string& condition) const override {
        return content.find(condition) != std::string::npos || author.find(condition) != std::string::npos;
    }
};

class Proverb : public Wisdom {
public:
    std::string country;

    Proverb(const std::string& c, const std::string& co) : Wisdom(c), country(co) {}

    std::string getType() const override {
        return "Proverb";
    }

    bool matchesCondition(const std::string& condition) const override {
        return content.find(condition) != std::string::npos || country.find(condition) != std::string::npos;
    }
};

class WisdomContainer {
private:
    std::vector<Wisdom*> wisdoms;

public:
    ~WisdomContainer(); // Declaration of the destructor

    void add(Wisdom* wisdom);
    void remove(const std::string& condition);
    void print() const;
};


#endif // WISDOM_CONTAINER_H