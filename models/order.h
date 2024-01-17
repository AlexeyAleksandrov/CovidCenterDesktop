#ifndef ORDER_H
#define ORDER_H

#include <QList>

class Order
{
public:

    enum class OrderStatus
    {
        CREATED,
        IN_PROCESS,
        FINISHED
    };

    Order();
    Order(long userId, long orderId, const QList<long> &services, OrderStatus orderStatus);

    long getUserId() const;
    void setUserId(long newUserId);
    long getOrderId() const;
    void setOrderId(long newOrderId);
    const QList<long> &getServices() const;
    void setServices(const QList<long> &newServices);
    OrderStatus getOrderStatus() const;
    void setOrderStatus(OrderStatus newOrderStatus);
    const QString &getUserFullName() const;
    void setUserFullName(const QString &newUserFullName);

    static QString getNameOfOrderStatus(OrderStatus orderStatus);

private:
    long userId;    // id пользователя
    QString userFullName;   // имя пользователя
    long orderId;   // id заказа
    QList<long> services;   // список сервисов
    OrderStatus orderStatus;    // статус заказа
};

#endif // ORDER_H
