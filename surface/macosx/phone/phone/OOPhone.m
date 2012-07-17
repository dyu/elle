//
//  phone.m
//  phone
//
//  Created by Charles Guillot on 22/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "OOPhone.h"
#import "OOManifestParser.h"
#import "OORestResquest.h"

NSString *OOUpdateProgessChangedNotification = @"OOUpdateProgessChangedNotification";

@implementation OOPhone

@synthesize _gap_State;

+(OOPhone *)getInstance{
    
    static OOPhone *singleton;
    @synchronized(self){
        if (!singleton){
            // Le singleton n'a pas encore été instancié
            singleton = [[OOPhone alloc] init];
        }
        return singleton;
    }
    
}

- (id)init {
    if (self = [super init]) {
        self._gap_State = gap_new();
    }
    return self;
}

- (void)dealloc {
    [self addOperationWithBlock:^(void) {
        gap_free(self._gap_State);
    }];
}

- (void)metaIsRespondingWithPerformSelector:(SEL)arg1 forObject:(id)arg2 {
    [self addOperationWithBlock:^(void) {
        //gap_Status response = gap_meta_status(self._gap_State);
        [arg2 performSelectorOnMainThread:arg1 withObject:[NSNumber numberWithInt:0] waitUntilDone:NO];
    }];
}

- (void)loginWithEmail:(NSString*)arg1 
              password:(NSString*)arg2 
       performSelector:(SEL)arg3 
             forObject:(id)arg4 {
    [self addOperationWithBlock:^(void) {
        /*gap_Status response =  gap_login(self._gap_State,
                                         [arg1 cStringUsingEncoding:NSASCIIStringEncoding],
                                         [arg2 cStringUsingEncoding:NSASCIIStringEncoding]);*/
        [arg4 performSelectorOnMainThread:arg3 withObject:[NSNumber numberWithInt:0] waitUntilDone:NO];
    }];
}

- (void)registerWithFullName:(NSString*)arg1 
                       email:(NSString*)arg2 
                    password:(NSString*)arg3 
                 machineName:(NSString*)arg4 
             performSelector:(SEL)arg5 
                   forObject:(id)arg6 {
    [self addOperationWithBlock:^(void) {
        gap_Status response = gap_register(self._gap_State,
                                           [arg1 cStringUsingEncoding:NSASCIIStringEncoding],
                                           [arg2 cStringUsingEncoding:NSASCIIStringEncoding],
                                           [arg3 cStringUsingEncoding:NSASCIIStringEncoding],
                                           [arg4 cStringUsingEncoding:NSASCIIStringEncoding]);
        [arg6 performSelectorOnMainThread:arg5 withObject:[NSNumber numberWithInt:0] waitUntilDone:NO];
    }];
}

- (char**)getUserNetworks {
    return gap_networks(self._gap_State);
}

- (void)update {
    OOManifestParser *parser = [[OOManifestParser alloc] init];
    [parser startParse:@"http://download.infinit.im/macosx64/manifest.xml"];
}

@end
