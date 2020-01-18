#pragma once

#include <memory>

#include "FactoryBase.h"
#include "MapObject.h"
#include "Items.h"
#include "Guard.h"



class MapObjectFactory : public FactoryBase<MapObject> // factory for map object
{};


class ItemFactory : public FactoryBase<Items>
{};

class GuardFactory : public FactoryBase<Guard>
{};