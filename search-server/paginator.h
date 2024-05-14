#pragma once
#include "document.h"
template<typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end) {
        begin_ = begin;
        end_ = end;
    }
    Iterator begin() const
    {
        return begin_;
    }
    Iterator end() const
    {
        return end_;
    }
    size_t size() const
    {
        return distance(begin_, end_);
    }

private:
    Iterator begin_;
    Iterator end_;
};

template<typename Iterator>
std::ostream& operator<<(std::ostream& out, const IteratorRange<Iterator>& range)
{
    for (auto i = range.begin(); i < range.end(); ++i)
        out << *i;
    return out;
}
template<typename Iterator>
class Paginator
{
public:
    Paginator(Iterator begin, Iterator end, size_t size)
    {

        Iterator it = begin;
        while (it != end)
        {
            Iterator current_end;
            current_end = next(it, std::min(static_cast<int>(size), static_cast<int>(distance(it, end))));
            pages_.push_back({ it,current_end });
            it = current_end;
        }
    }
    auto begin() const {
        return pages_.begin();
    }
    auto end() const {
        return pages_.end();
    }
private:
    std::vector<IteratorRange<Iterator>>pages_;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}