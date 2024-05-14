#include<iostream>
#include "document.h"
std::ostream& operator<<(std::ostream& out, const Document& it)
{
    out << "{ document_id = " << it.id << ", relevance = " << it.relevance << ", rating = " << it.rating << " }";
    return out;
}