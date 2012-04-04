//
//  FIListCellDictKey.m
//  HelperTools
//
//  Created by Charles Guillot on 30/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FIListCellDictKey.h"
#import <objc/objc-class.h>
#import "ZombieDictKey.h"

@implementation FIListCellDictKey

@synthesize cell;
@synthesize nodeStatus;

static char overviewKey;
static NSMutableSet *items = nil;

+ (id)listCellDictKeyWithCell:(id)arg1
{
    @synchronized(items)
    {
        if (items == nil) {
            items = [[NSMutableSet alloc] init];
        }
        FIListCellDictKey *matchItem = nil;
        for (FIListCellDictKey *item in [items allObjects]) {
            if (item.cell != nil) {
                if (item.cell == arg1) {
                    matchItem = item;
                    break;
                }
            }
        }
        
        if (matchItem == nil)
        {
            matchItem = [[FIListCellDictKey alloc] initWithCell:arg1];
            [items addObject:matchItem];
            ZombieDictKey *zombieReleaser = objc_getAssociatedObject(arg1, &overviewKey);
            
            if (zombieReleaser == nil) {
                zombieReleaser = [[ZombieDictKey alloc] init];
                objc_setAssociatedObject ( arg1, &overviewKey, zombieReleaser, OBJC_ASSOCIATION_RETAIN );
            }
            [zombieReleaser addDictKey:matchItem];
            
            [zombieReleaser release];
        }
        
        return matchItem;
    }
}

- (id) initWithCell:(id)arg1
{
    self = [super init];
    
    self.cell = arg1; // TODO add release link
    self.nodeStatus = FINodeStatusUnknowned;
    
    [[FIIconOverlay instance] addStatusOpperationToQueue:self];
    
    return self;
}
-(void)dealloc
{
    [super dealloc];
}
- (unsigned long long)hash
{
    if (self.cell == nil)
        return 0;
    return [self.cell hash];
}
- (BOOL)isEqual:(id)arg1
{
    if (arg1 == self)
        return YES;
    if (!arg1 || ![arg1 isKindOfClass:[self class]])
        return NO;
    if (self.cell == nil || ((FIListCellDictKey *)arg1).cell == nil)
        return NO;
    return self.cell == ((FIListCellDictKey *)arg1).cell;
}

- (NSURL *) getPath
{
    if (self.cell == nil)
        return nil;
    
    if ([self.cell respondsToSelector:@selector(node)]) {
        NSURL *path = [NSURL fileURLWithPath:[[NSClassFromString(@"NSNavFBENode") _nodeWithFBENode:((TFENode *)[self.cell node])->fNodeRef] path]];
        
        return [path autorelease];
    }
    else {
        return nil;
    }
}

- (void) refreshCell
{   
    if (self.cell == nil)
        return;
    
    if ([self.cell respondsToSelector:@selector(controlView)]) {
        [[self.cell controlView] updateCell:cell];
    }
}

- (void) cleanUp
{
    self.cell = nil;
    @synchronized(items)
    {
        if ([items containsObject:self]){
            [items removeObject:self];
        }
    }
    [self release];
    [self cancel];
    
}

- (void) main
{
    NSAutoreleasePool *oppPool = [[NSAutoreleasePool alloc] init];
    if (self != nil && !self.isCancelled)
    {
        NSURL* url = [self getPath];
        NSString *filename = [[url path] lastPathComponent];
        
        NSString *firstChar = [filename substringToIndex:1];
        
        // Get status by path
        sleep(1);
        // Set status
        if ([firstChar isEqualToString:@"A"])
        {
            [self setNodeStatus:FINodeStatusDisconected];
        }
        
        if ([self respondsToSelector:@selector(refreshCell)]) {
            [self performSelectorOnMainThread:@selector(refreshCell) withObject:nil waitUntilDone:NO];
        }
    }
    [oppPool drain];
}


@end
