#include "stdafx.h"
#include "collective_name.h"
#include "creature.h"
#include "entity_name.h"


template <class Archive>
void CollectiveName::serialize(Archive& ar, const unsigned int version) {
  serializeAll(ar, fullName, shortName, raceName);
}

SERIALIZABLE(CollectiveName);

SERIALIZATION_CONSTRUCTOR_IMPL(CollectiveName);

CollectiveName::CollectiveName(optional<string> race, optional<string> location, const Creature* leader) {
  if (location && race)
    fullName = capitalFirst(*race) + " of " + *location;
  else if (auto first = leader->getFirstName())
    fullName = *first + " the " + leader->getName().bare();
  else if (race)
    fullName = capitalFirst(*race);
  else
    fullName = leader->getNameAndTitle();
  if (location)
    shortName = *location;
  else
    shortName = leader->getFirstName().get_value_or(leader->getName().bare());
  if (race)
    raceName = *race;
  else
    raceName = leader->getSpeciesName();
}

const string& CollectiveName::getShort() const {
  return shortName;
}

const string& CollectiveName::getFull() const {
  return fullName;
}

const string& CollectiveName::getRace() const {
  return raceName;
}

