#ifndef MAKISE_E_SLIST_H
#define MAKISE_E_SLIST_H        1

#include "makise_config.h"

#if ( MAKISE_E_SLIST > 0 )

#ifdef __cplusplus
extern "C" {
#endif

#include "makise_e.h"

typedef struct {
    uint32_t bg_color;
    uint32_t font_col;
    uint32_t border_c;

    uint16_t double_border;
} MakiseStyleTheme_SList;

typedef struct {
    const MakiseFont * font;
    uint32_t font_line_spacing;

    MakiseStyleTheme_SList normal;
    MakiseStyleTheme_SList focused;
    MakiseStyleTheme_SList active;
} MakiseStyle_SList;

// Simple list element.
// Can display items. Supports scrolling.
// Modes: list, radio buttons, checkboxes.
typedef enum {
    MSList_List,
    MSList_RadioButton,
    MSList_Checkbox
} MSList_Type;

typedef struct _MSList_Item MSList_Item;
typedef struct _MSList MSList;

typedef struct _MSList_Item {
    char*                   text;           // text of item
    uint32_t                value;          // value. It may be checkbox or radio button status

    MSList_Item*            prev;
    MSList_Item*            next;

    uint32_t                id;             // c ustom id, if NOT is_array, else - position in the array(will be computed automatically by MSList).
} MSList_Item;

typedef struct _MSList {
    MakiseGUI*              gui;
    MElement                el;

    char*                   text;

    MSList_Item*            items;          // item's array pointer or pointer to the first element of the list
    uint8_t                 is_array;       // if 1 then items will be
    uint32_t                len;            // matters only if is_array

    MSList_Item*            selected;

#if MAKISE_GUI_INPUT_POINTER_ENABLE == 1
    uint8_t                 started;        // was pressing already started
    int32_t                 sx;             // cursor's x when pressing was started
    int32_t                 sy;
    MSList_Item*            sitem;          // focused item when pressing was started
#endif

    void                    ( *onselection )  ( MSList *l, MSList_Item *selected );     // when selected item is changing
    void                    ( *click )        ( MSList *l, MSList_Item *selected );     // when OK button clicked

    MSList_Type             type;
    MakiseStyle_SList*       style;
    MakiseStyle_SList*       item_style;

    uint32_t                state;          // focus state
} MSList;

void m_create_slist( MSList*                b,
                     MContainer*            c,
                     MPosition              pos,
                     char*                  text,
                     void                   ( *onselection )    ( MSList *l, MSList_Item *selected ),
                     void                   ( *click )          ( MSList *l, MSList_Item *selected ),
                     MSList_Type            type,
                     MakiseStyle_SList*      style,
                     MakiseStyle_SList*      item_style);

void m_slist_add        ( MSList *l, MSList_Item *item );                   // Add one item to the list at the end. Only if NOT is_array.
void m_slist_clear      ( MSList *l);                                       // Clear all pointers
void m_slist_remove     ( MSList *l, MSList_Item *item );                   // Remove item from linked list. Only if NOT is_array.
void m_slist_set_array  ( MSList *l, MSList_Item *array, uint32_t len );    // Set new data source. Simple array.
void m_slist_set_list   ( MSList *l, MSList_Item *first );                  // Set linked list as new data source.

/* void m_slist_set_onselection(MSList *l, void (*onselection)(MSList *l, MSList_Item selected)); */
/* void m_slist_set_click(MSList *l, void (*click)(MSList *l, MSList_Item selected)); */

#ifdef __cplusplus
}
#endif

#endif

#endif

