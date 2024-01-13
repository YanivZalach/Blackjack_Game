#pragma once

// Includes
#include <memory>
#include <vector>
#include "classes.h"

// Consts
const int NUMOFGROUPSINDEAK = 4;

// Creating the deck of cards - private to this file
std::vector<std::unique_ptr<Card>> crateDeakOfCards();

// Returning the deck of cards - Shuffled
std::vector<std::unique_ptr<Card>> shffelDeakOfCards();


