#include "TowerNode.h"

using namespace ntw::abstr;

ntw::abstr::TowerNode::TowerNode()
{
    maxSize = to_int(TowerSize::Default);
}

ntw::abstr::TowerNode::TowerNode(const TowerNode& src) :
    maxSize(src.maxSize)
{
    ConnectedSubs = src.ConnectedSubs;
}

ntw::abstr::TowerNode::TowerNode(TowerNode&& from) noexcept :
    maxSize(from.maxSize)
{
	ConnectedSubs.assign(from.ConnectedSubs.begin(), from.ConnectedSubs.end());
    from.ConnectedSubs.clear();
}

ntw::abstr::TowerNode::TowerNode(const TowerSize& size)
{
    maxSize = to_int(size);
}

ntw::abstr::TowerNode::~TowerNode()
{
    for (TowerNode* element : ConnectedSubs) {
        element->removeConnect(this);
    }
}

TowerNode& ntw::abstr::TowerNode::operator=(const TowerNode& src)
{
    if (&src != this) {
        maxSize = src.maxSize;
		ConnectedSubs.assign(src.ConnectedSubs.begin(), src.ConnectedSubs.end());
    }
    return *this;
}

TowerNode &ntw::abstr::TowerNode::operator=(TowerNode &&from) noexcept
{
    if (&from != this) {
        maxSize = from.maxSize;
		ConnectedSubs.assign(from.ConnectedSubs.begin(), from.ConnectedSubs.end());
        from.ConnectedSubs.clear();
    }
    return *this;
}

int ntw::abstr::TowerNode::addConnect(TowerNode* pNode)
{
    if (ConnectedSubs.size() == maxSize) {
        return 4;
    }
    if (pNode == this) {
        return 1;
    }
    if (isConnected(pNode)) {
        return 2;
    }

    ConnectedSubs.push_back(pNode);
    return 0;
}

/// @todo Отладка метода
int ntw::abstr::TowerNode::removeConnect(TowerNode* pNode)
{
    Iterator toRemove;
    if (isConnected(pNode, toRemove)) {
        ConnectedSubs.erase(toRemove);
        return 0;
    }
    return 3;
}

int ntw::abstr::TowerNode::removeConnect(int nConnection)
{
    Iterator toRemove = ConnectedSubs.begin();
    for (int i = 0; i < nConnection; ++i, ++toRemove);
    if (toRemove != ConnectedSubs.end()) {
        ConnectedSubs.erase(toRemove);
        return 0;
    }
    return 3;
}

void ntw::abstr::TowerNode::removeLastConnect()
{
    ConnectedSubs.pop_back();
}

TowerNode::Iterator TowerNode::Begin() noexcept
{
    return ConnectedSubs.begin();
}

TowerNode::Iterator ntw::abstr::TowerNode::End() noexcept
{
    return ConnectedSubs.end();
}

bool ntw::abstr::TowerNode::isConnected(TowerNode* pTower)
{
    Iterator toRemove = ConnectedSubs.begin();
    bool isFound = false;
    while (!isFound && toRemove != ConnectedSubs.end())
    {
        isFound = *toRemove == pTower;
        ++toRemove;
    }

    return isFound;
}

bool ntw::abstr::TowerNode::isConnected(TowerNode* pTower, Iterator& seekIterator)
{
    seekIterator = ConnectedSubs.begin();
    bool isFound = false;
    while (!isFound && seekIterator != ConnectedSubs.end())
    {
        isFound = *seekIterator == pTower;
        ++seekIterator;
    }

    if (isFound) --seekIterator;
    return isFound;
}

int ntw::abstr::TowerNode::getConnectedCount() const noexcept
{
    return ConnectedSubs.size();
}

int ntw::abstr::TowerNode::getConnectedLimit() const noexcept
{
    return maxSize;
}

TowerNode* ntw::abstr::TowerNode::getAt(int nConnection)
{
    //Iterator it = Begin();
    //for (int i = 0; i < nConnection && it != End(); ++i, ++it);
    //return it != End() ? *it : nullptr;
    return ConnectedSubs[nConnection];
}
