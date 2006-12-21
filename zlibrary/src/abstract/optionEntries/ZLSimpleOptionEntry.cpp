/*
 * Copyright (C) 2004-2006 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "ZLSimpleOptionEntry.h"

ZLSimpleStringOptionEntry::ZLSimpleStringOptionEntry(const std::string &name, ZLStringOption &option) : myName(name), myOption(option) {
}

const std::string &ZLSimpleStringOptionEntry::name() const {
	return myName;
}

const std::string &ZLSimpleStringOptionEntry::initialValue() const {
	return myOption.value();
}

void ZLSimpleStringOptionEntry::onAccept(const std::string &value) {
	myOption.setValue(value);
}

ZLSimpleBooleanOptionEntry::ZLSimpleBooleanOptionEntry(const std::string &name, ZLBooleanOption &option) : myName(name), myOption(option) {
}

const std::string &ZLSimpleBooleanOptionEntry::name() const {
	return myName;
}

bool ZLSimpleBooleanOptionEntry::initialState() const {
	return myOption.value();
}

void ZLSimpleBooleanOptionEntry::onAccept(bool state) {
	myOption.setValue(state);
}

ZLSimpleSpinOptionEntry::ZLSimpleSpinOptionEntry(const std::string &name, ZLIntegerRangeOption &option, int step) : myName(name), myOption(option), myStep(step) {
}

const std::string &ZLSimpleSpinOptionEntry::name() const {
	return myName;
}

int ZLSimpleSpinOptionEntry::initialValue() const {
	return myOption.value();
}

int ZLSimpleSpinOptionEntry::minValue() const {
	return myOption.minValue();
}

int ZLSimpleSpinOptionEntry::maxValue() const {
	return myOption.maxValue();
}

int ZLSimpleSpinOptionEntry::step() const {
	return myStep;
}

void ZLSimpleSpinOptionEntry::onAccept(int value) {
	myOption.setValue(value);
}

std::vector<std::string> ZLSimpleBoolean3OptionEntry::ourValues;

ZLSimpleBoolean3OptionEntry::ZLSimpleBoolean3OptionEntry(const std::string &name, ZLBoolean3Option &option) : myName(name), myOption(option) {
}

const std::string &ZLSimpleBoolean3OptionEntry::name() const {
	return myName;
}

const std::string &ZLSimpleBoolean3OptionEntry::initialValue() const {
	return values()[myOption.value()];
}

const std::vector<std::string> &ZLSimpleBoolean3OptionEntry::values() const {
	if (ourValues.empty()) {
		ourValues.push_back("No");
		ourValues.push_back("Yes");
		ourValues.push_back("<base>");
	}
	return ourValues;
}

void ZLSimpleBoolean3OptionEntry::onAccept(const std::string &value) {
	for (unsigned int i = 0; i < values().size(); ++i) {
		if (values()[i] == value) {
			myOption.setValue((Boolean3)i);
			return;
		}
	}
}

ZLSimpleColorOptionEntry::ZLSimpleColorOptionEntry(const std::string &name, ZLColorOption &option) : myName(name), myOption(option) {
}

const ZLColor ZLSimpleColorOptionEntry::color() const {
	return myOption.value();
}

void ZLSimpleColorOptionEntry::onAccept(ZLColor color) {
	myOption.setValue(color);
}

const std::string &ZLSimpleColorOptionEntry::name() const {
	return myName;
}