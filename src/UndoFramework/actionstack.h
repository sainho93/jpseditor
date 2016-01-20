#ifndef ACTIONSTACK_H
#define ACTIONSTACK_H

#include <QStack>
#include "action.h"
#include "paintaction.h"

class ActionStack
{
public:
    ActionStack();
    ~ActionStack();

    LineAction GetRecentAction();
    void PushNewAction(const LineAction& action);
private:
    QStack<LineAction> _actionstack;
};

#endif // ACTIONSTACK_H
