#include <vector>
#include <string>
#include <algorithm>
#include "search_server.h"
#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) : search_server_(search_server) {
   
}
// сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status)
{
    std::vector<Document> result = search_server_.FindTopDocuments(raw_query, status);
    while (requests_.size() >= min_in_day_)
    {
        requests_.pop_front();
    }
    requests_.push_back({ current_time_, result });
    current_time_ += 1;
    return result;
}
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query)
{
    std::vector<Document> result = search_server_.FindTopDocuments(raw_query);
    while (requests_.size() >= min_in_day_)
    {
        requests_.pop_front();
        current_time_ = 1;
    }
    requests_.push_back({ current_time_, result });
    current_time_ += 1;
    return result;
}
int RequestQueue::GetNoResultRequests() const {
    // напишите реализацию
    return static_cast<int>(std::count_if(requests_.begin(), requests_.end(), [](const QueryResult& lhs) {
        return lhs.results.empty();
        }));
}