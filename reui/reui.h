/*
 * reui.h -- reui main API
 */

#ifndef REUI_H
#define REUI_H

#include <stdbool.h>
#include <stdint.h>

/*** config ***/

#ifndef REUI_MAX_CHILDREN
#    define REUI_MAX_CHILDREN UINT16_MAX
#endif

/*** types ***/

typedef struct mesgmap   MesgMap;
typedef struct mesgnode  MesgNode;
typedef struct mesgqueue MesgQueue;
typedef struct mesgassoc MesgAssoc;
typedef struct uimap     UIMap;
typedef struct widget    Widget;
typedef struct win       Win;
typedef struct point     Point;
typedef struct rect      Rect;
typedef struct size      Size;
typedef struct event     Event;
typedef struct style     Style;
typedef struct layout    Layout;
typedef struct container Container;

typedef enum widgetkind {
	RWK_BCTR, /* base container */
	RWK_VSTACK,
	RWK_HSTACK,
	RWK_SCRSTACK,
	RWK_GRID,
	RWK_TABBED,

	RWK_LABEL,
	RWK_TEXTENTRY,
	RWK_BTN,
	RWK_COMBOBOX,
	RWK_DROPDWN,
	RWK_CANVAS,
} WidgetKind;

typedef enum evkind {
	REV_NONE,
	REV_CLICK,
	REV_CHANGE,
	REV_FOCUS,
	REV_BLUR,
	REV_KEYDOWN,
	REV_KEYUP,
	REV_MOUSEMOVE,
	REV_MOUSEUP,
	REV_MOUSEDOWN,
	REV_SCROLL,
	REV_RESIZE,
	REV_CLOSE,
	REV_USER
} EventKind;

typedef enum align {
	RAL_START,
	RAL_CENTER,
	RAL_END,
	RAL_STRETCH,
} Align;

typedef enum orientation {
	ROR_HORIZ,
	ROR_VERT,
} Orientation;

typedef enum visibility {
	RVS_VIS,
	RVS_HIDDEN,
	RVS_COLLAPSED,
} Visibility;

typedef enum msgres {
	RMR_IGNORE,
	RMR_HANDLED,
	RMR_STOP
} MsgRes;

struct style {
	uint32_t fore, back;
	uint32_t bordercol;
	uint16_t bordersiz;
	uint16_t padding;
	uint16_t margin;
	uint8_t opacity;
};

struct layout {
	Orientation orient;
	Align main_align;
	Align cross_align;

	uint16_t spacing;
	uint16_t cols;
	uint16_t rows;
};

struct event {
	EventKind evk;
	Widget *targ;

	union {
		struct {
			int32_t x, y;
		} mouse;
		struct {
			int32_t key;
		} kbd;
		struct {
			int32_t x, y;
		} scrl;
		struct {
			uint32_t w, h;
		} resiz;
		struct {
			const char *text;
		} change;
		void *userdata;
	} data;

	bool handled;
};

typedef void (*EventCallback)(Widget *widget, Event *event, void *userdata);
typedef void (*MesgCallback)(Widget widget, uint32_t ev, void *userdata);

#ifdef _IN_REUI
/* only sources inside reui can see this */

struct point {
	int32_t x;
	int32_t y;
};

struct rect {
	Point bl;
	Point tr;
};

struct mesgassoc {
	MesgAssoc *next;
	uint32_t ev;
	MesgCallback cb;
	void *udata;
	bool enabled;
};

struct mesgmap {
	MesgAssoc *first;
	MesgAssoc *last;
	uint32_t count;
};

struct mesgqueue {
	MesgQueue *next;
	MesgMap *map;
};

struct mesgnode {
	MesgNode *next;
	Widget *w;
	uint32_t ev;
	MesgCallback cb;
	void *userdata;
};

struct uimap {
	Widget *root;
	Win *win;
};

struct widget {
	WidgetKind kind;
	Widget *parent;
	Widget *children;
	Widget *next;
	MesgAssoc *assocs;
	Rect bounds;
	MesgMap mesgs;
	uint16_t nchild;
};

struct container {
	Widget *next;
	Widget *val;
};

struct size {
	uint32_t w;
	uint32_t h;
};

struct win {
	char *title;
	Rect size_and_pos;
};
#endif /* _IN_REUI */

/*** functions ***/
bool evs_pending(void);
void reui_iterate(MesgMap *assocs);
uint32_t dispatch_mesgs(MesgMap *assocs);
void mesg_assoc(Widget *w, uint32_t ev, MesgCallback cb, void *userdata);
void mesg_disassoc(Widget *w, uint32_t ev, MesgCallback cb);
void reui_setup(void);
void reui_teardown(void);
void win_destroy(Win *win);
Win *win_new(const char *title, const Rect posAndSize);
bool win_shouldclose(Win *win);

#endif /* REUI_H */
