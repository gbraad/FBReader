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

#include "ZLZip.h"
#include "ZLZDecompressor.h"

ZLGzipInputStream::ZLGzipInputStream(shared_ptr<ZLInputStream> stream) : myFileStream(stream), myFileSize(0) {
}

ZLGzipInputStream::~ZLGzipInputStream() {
	close();
}

bool ZLGzipInputStream::open() {
	close();

	if (!myFileStream->open()) {
		return false;
	}

	myFileSize = myFileStream->sizeOfOpened();

	unsigned char id1;
	unsigned char id2;
	unsigned char cm;

	myFileStream->read((char*)&id1, 1);
	myFileStream->read((char*)&id2, 1);
	myFileStream->read((char*)&cm, 1);
	if ((id1 != 31) || (id2 != 139) || (cm != 8)) {
		myFileStream->close();
		return false;
	}

	//const unsigned char FTEXT = 1 << 0;
	const unsigned char FHCRC = 1 << 1;
	const unsigned char FEXTRA = 1 << 2;
	const unsigned char FNAME = 1 << 3;
	const unsigned char FCOMMENT = 1 << 4;
	unsigned char flg;
	myFileStream->read((char*)&flg, 1);
	myFileStream->seek(6, false);
	if (flg & FEXTRA) {
		unsigned char b0, b1;
		myFileStream->read((char*)&b0, 1);
		myFileStream->read((char*)&b1, 1);
		unsigned short xlen = ((unsigned short)b1) << 8 + b0;
		myFileStream->seek(xlen, false);
	}
	if (flg & FNAME) {
		unsigned char b;
		do {
			myFileStream->read((char*)&b, 1);
		} while (b != 0);
	}
	if (flg & FCOMMENT) {
		unsigned char b;
		do {
			myFileStream->read((char*)&b, 1);
		} while (b != 0);
	}
	if (flg & FHCRC) {
		myFileStream->seek(2, false);
	}

	myDecompressor = new ZLZDecompressor(myFileSize - myFileStream->offset() - 8);
	myOffset = 0;

	return true;
}

size_t ZLGzipInputStream::read(char *buffer, size_t maxSize) {
	size_t realSize = myDecompressor->decompress(*myFileStream, buffer, maxSize);
	myOffset += realSize;
	return realSize;
}

void ZLGzipInputStream::close() {
	myDecompressor = 0;
	myFileStream->close();
}

void ZLGzipInputStream::seek(int offset, bool absoluteOffset) {
  if (absoluteOffset) {
    offset -= this->offset();
  }
  if (offset > 0) {
    read(0, offset);
  } else if (offset < 0) {
    offset += this->offset();
		open();
    if (offset >= 0) {
      read(0, offset);
    }
  }
}

size_t ZLGzipInputStream::offset() const {
	return myOffset;
}

size_t ZLGzipInputStream::sizeOfOpened() {
	// TODO: implement
	return 0;
}
