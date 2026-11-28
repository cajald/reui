/*
 * reui.h -- reui main API
 */

#ifndef REUI_H
#define REUI_H

#include <stdbool.h>
#include <stdint.h>

/*** types ***/

typedef struct mesgmap MesgMap;
typedef struct uimap   UIMap;
typedef struct widget  Widget;
typedef struct win     Win;
typedef struct point   Point;
typedef struct rect    Rect;

typedef void(*MesgCallback)(Widget widget, void* userdata);

#if !defined(_IN_REUI)
/* don't let others see the internal values */
struct mesgmap;
struct uimap;
struct widget;
struct win;
struct point;
struct rect
#else
/* only sources inside reui can see this */

struct mesgmap
{
	MesgMap* next;
	MesgCallback* val;
};

struct uimap
{
	Widget* root;
	Win* win;
};

struct widget
{
	Widget* child;
	Widget* parent;
	uint16_t nchild;
};

struct container
{
	Widget* next;
	Widget* val;
};

struct rect
{
	Point* bl;
	Point* tr;
};

struct point
{
	int32_t x;
	int32_t y;
};

struct win
{
	char* title;
	Rect size_and_pos;
};
#endif /* _IN_REUI */

/*** functions ***/

Win* win_new(const char* title, const Rect posAndSize);
bool win_shouldclose(Win* win);

#endif /* REUI_H */
