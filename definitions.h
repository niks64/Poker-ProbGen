#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <sstream>


enum suit {SPADE = 4, HEART = 3, DIAMOND = 2, CLUB = 1};
enum value {two=2, three=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10, jack=11, queen=12, king=13, ace=14};

static std::unordered_map<suit, std::string> suitStrings = {
    {SPADE, "\u2660"},
    {DIAMOND, "\u2661"},
    {HEART, "\u2662"},
    {CLUB, "\u2663"}
};

static std::unordered_map<value, std::string> valueStrings = {
    {two, "2"},
    {three, "3"},
    {four, "4"},
    {five, "5"},
    {six, "6"},
    {seven, "7"},
    {eight, "8"},
    {nine, "9"},
    {ten, "T"},
    {jack, "J"},
    {queen, "Q"},
    {king, "K"},
    {ace, "A"}
};

static std::unordered_map<char, suit> charSuits = {
    {'s', SPADE},
    {'d', DIAMOND},
    {'h', HEART},
    {'c', CLUB}
};

static std::unordered_map<char, value> charValues = {
    {'2', two},
    {'3', three},
    {'4', four},
    {'5', five},
    {'6', six},
    {'7', seven},
    {'8', eight},
    {'9', nine},
    {'T', ten},
    {'J', jack},
    {'Q', queen},
    {'K', king},
    {'A', ace}
};

static std::unordered_map<int, std::string> handTypes = {
    {0, "BAD"},
    {1, "High Card"},
    {2, "Pair"},
    {3, "Two Pair"},
    {4, "Trips"},
    {5, "Straight"},
    {6, "Flush"},
    {7, "Full House"},
    {8, "Quads"},
    {9, "Straight Flush"},
};

const int NUM_VALUES= 13;
const int NUM_SUITS = 4;

const int SUIT_STRING_LENGTH = 3;
const int VALUE_STRING_LENGTH = 3;
const int TOTAL_CARD_LENGTH = 4;
const int TEXAS_HAND_STRING_LENGTH = 2 * TOTAL_CARD_LENGTH;

#endif