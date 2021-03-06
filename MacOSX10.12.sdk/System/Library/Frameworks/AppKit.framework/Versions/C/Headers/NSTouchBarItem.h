/*
 NSTouchBarItem.h
 Application Kit
 Copyright (c) 2015-2016, Apple Inc.
 All rights reserved.
*/

#import <AppKit/AppKitDefines.h>

#import <Foundation/Foundation.h>

typedef NSString * NSTouchBarItemIdentifier NS_EXTENSIBLE_STRING_ENUM;

@class NSTouchBar, NSViewController, NSView, NSImage, NSGestureRecognizer;
@class NSString;

NS_ASSUME_NONNULL_BEGIN

typedef float NSTouchBarItemPriority _NS_TYPED_EXTENSIBLE_ENUM NS_AVAILABLE_MAC(10_12_2);

static const NSTouchBarItemPriority NSTouchBarItemPriorityHigh NS_AVAILABLE_MAC(10_12_2) = 1000;
static const NSTouchBarItemPriority NSTouchBarItemPriorityNormal NS_AVAILABLE_MAC(10_12_2) = 0;
static const NSTouchBarItemPriority NSTouchBarItemPriorityLow NS_AVAILABLE_MAC(10_12_2) = -1000;


NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSTouchBarItem : NSObject <NSCoding> {
@private
    NSTouchBarItemIdentifier _identifier;
    NSTouchBarItemPriority _visibilityPriority;
    NSInteger _visibilityCount;
    NSMapTable<NSTouchBar *, NSNumber *> *_touchBars;

#if !__OBJC2__
    void *_touchBarItemReserved[4] __unused;
#endif /* !__OBJC2__ */
}

/*
    The designated initializer. This instantiates a new touch bar item with the specified initializer.
*/
- (instancetype)initWithIdentifier:(NSTouchBarItemIdentifier)identifier NS_DESIGNATED_INITIALIZER;

/*
    Items can be archived and unarchived using NSCoder, as noted by conformance to the NSCoding protocol.
*/
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/*
    Items must be instantiated with an identifier. Use -initWithIdentifier instead of -init.
*/
- (instancetype)init NS_UNAVAILABLE;

/*
    The identifier of this item. Apart from spaces, item identifiers should be globally unique.
*/
@property (readonly, copy) NSTouchBarItemIdentifier identifier;

/*
    If there are more items in the touch bar than can be displayed, some will be hidden. Items with high visibility priority will be hidden after items with low visibility priority.
*/
@property NSTouchBarItemPriority visibilityPriority;

/*
    Intended for subclassing. By default, this method returns this item's view controller's view.
*/
@property (readonly, nullable) NSView *view;

/*
    Intended for subclassing. By default, this method returns nil.
*/
@property (readonly, nullable) NSViewController *viewController;

/*
    The user visible string identifying this item during customization. By default this method returns the empty string.
*/
@property (readonly, copy) NSString *customizationLabel;

/*
    When YES, this item is attached to a visible touch bar, and is being displayed. Note that some types of items are never considered visible, for example spaces, other items proxys, and groups.
    This property is key value observable.
*/
@property (readonly, getter=isVisible) BOOL visible;
@end

/*
    The identifier of an item appropriate for use as a small space in the touch bar. Generally, you can use this identifier in a touch bar's itemIdentifiers array, and it will instantiate that space for you.
*/
APPKIT_EXTERN NSTouchBarItemIdentifier const NSTouchBarItemIdentifierFixedSpaceSmall NS_AVAILABLE_MAC(10_12_2);

/*
    The identifier of an item appropriate for use as a large space in the touch bar. Generally, you can use this identifier in a touch bar's itemIdentifiers array, and it will instantiate that space for you.
*/
APPKIT_EXTERN NSTouchBarItemIdentifier const NSTouchBarItemIdentifierFixedSpaceLarge NS_AVAILABLE_MAC(10_12_2);

/*
    The identifier of an item appropriate for use as a flexible space in the touch bar. Generally, you can use this identifier in a touch bar's itemIdentifiers array, and it will instantiate that space for you.
*/
APPKIT_EXTERN NSTouchBarItemIdentifier const NSTouchBarItemIdentifierFlexibleSpace NS_AVAILABLE_MAC(10_12_2);

/*
    The identifier of the special "other items proxy." Generally, you can use this identifier in a touch bar's itemIdentifiers array, and a special proxy item will be instantiated for you. When the touch bar containing this item is visible, touch bars provided by items closer to the first responder will be nested inside the space denoted for this item. Space items on either side of this item will be automatically massaged to handle cases where the touch bar containing this identifier is itself the bar closest to the first responder (or closer bars are empty.)
    Note that a touch bar lacking this item identifier will be replaced in its entirety by touch bars closer to the first responder.
*/
APPKIT_EXTERN NSTouchBarItemIdentifier const NSTouchBarItemIdentifierOtherItemsProxy NS_AVAILABLE_MAC(10_12_2);

NS_ASSUME_NONNULL_END
