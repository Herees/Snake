#include "cards.hh"
#include <iostream>
#include <memory>

Cards::Cards()
{
    top_ = nullptr;
}

void Cards::add(int id)
{
    std::shared_ptr<Card_data> new_card
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_= new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    if (top_ == nullptr){
        return;
    }
    auto examined = top_;
    int i = 1;
    while (true)
    {
        s<<i<<": "<<examined->data<<'\n';
        examined = examined->next;
        i++;
        if (examined == nullptr)
        {
            break;
        }
    }
}

bool Cards::remove(int& id)
{
    if (top_ == nullptr)
    {
        return false;
    }
    auto temp = top_->next;
    id = top_->data;
    top_ = temp;
    return true;
}

bool Cards::bottom_to_top()
{
    if (top_ == nullptr)
    {
        return false;
    }
    auto examined = top_;
    if (examined->next == nullptr)
    {
        return true;
    }
    while (true)
    {

        if (examined->next->next == nullptr)
        {
            auto temp = examined->next;
            examined->next = nullptr;
            temp->next = top_;
            top_ = temp;
            return true;
        }
        examined = examined->next;
    }

}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
    {
        return false;
    }
    auto examined = top_;
    while (true)
    {
        if (examined->next == nullptr)
        {

            examined->next = top_;
            auto temp = top_;
            top_ = top_->next;
            temp->next = nullptr;
            return true;
        }
        examined = examined->next;
    }
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if (top_ == nullptr){
        return;
    }
    auto examiner = top_;
    auto examined = top_;
    int i = 1;
    while (true)
    {
        while (true)
        {

            if (examined->next == examiner)
            {
                s<<i<<": "<<examined->data<<'\n';
                i++;
                examiner = examined;
                examined = top_;
                break;
            }
            if (examined->next == nullptr)
            {
                s<<i<<": "<<examined->data<<'\n';
                i++;
                examiner = examined;
                examined = top_;
                break;
            }
            examined = examined->next;
        }
        if (examiner == top_)
        {
            break;
        }
    }
}

Cards::~Cards()
{
    auto examiner2 = top_->next;
    while (true)
    {
        auto temp = top_;
        top_ = examiner2;
        if (examiner2->next != nullptr)
        {
            examiner2 = examiner2->next;
        }
        if (examiner2->next == nullptr){
            break;
        }
    }
}
