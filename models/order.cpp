#include "order.h"

Order::Order()
{

}

Order::Order(long userId, long orderId, const QList<long> &services, Order::OrderStatus orderStatus) : userId(userId),
    orderId(orderId),
    services(services),
    orderStatus(orderStatus)
{}

long Order::getUserId() const
{
    return userId;
}

void Order::setUserId(long newUserId)
{
    userId = newUserId;
}

long Order::getOrderId() const
{
    return orderId;
}

void Order::setOrderId(long newOrderId)
{
    orderId = newOrderId;
}

const QList<long> &Order::getServices() const
{
    return services;
}

void Order::setServices(const QList<long> &newServices)
{
    services = newServices;
}

Order::OrderStatus Order::getOrderStatus() const
{
    return orderStatus;
}

void Order::setOrderStatus(OrderStatus newOrderStatus)
{
    orderStatus = newOrderStatus;
}

QString Order::getNameOfOrderStatus(OrderStatus orderStatus)
{
    switch (orderStatus)
    {
        case OrderStatus::CREATED:
        {
            return "СОЗДАН";
        }
        case OrderStatus::IN_PROCESS:
        {
            return "В ПРОЦЕССЕ";
        }
        case OrderStatus::FINISHED:
        {
            return "ЗАВЕРШЕН";
        }
        default:
        {
            return "";
        }
    }
}

const QString &Order::getUserFullName() const
{
    return userFullName;
}

void Order::setUserFullName(const QString &newUserFullName)
{
    userFullName = newUserFullName;
}

