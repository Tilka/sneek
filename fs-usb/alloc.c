/*

SNEEK - SD-NAND/ES emulation kit for Nintendo Wii

Copyright (C) 2009-2011  crediar

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation version 2.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/
#include "alloc.h"
#include "vsprintf.h"

void *malloc( u32 size )
{
	void *ptr = heap_alloc( 0, size );
	if( ptr == NULL )
	{
		dbgprintf("Malloc:%p Size:%08X FAILED\n", ptr, size );
		while(1);
	}
	return ptr;
}
void *malloca( u32 size, u32 align )
{
	void *ptr = heap_alloc_aligned( 0, size, align );
	if( ptr == NULL )
	{
		dbgprintf("Malloca:%p Size:%08X FAILED\n", ptr, size );
		while(1);
	}
	return ptr;
}
void free( void *ptr )
{
	if( ptr != NULL )
		heap_free( 0, ptr );

	//dbgprintf("Free:%p\n", ptr );

	return;
}