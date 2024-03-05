//
//  shiUIWebView.m
//
//  Created by Peter Spiske on 16.07.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "shiUIWebView.h"

@implementation shiUIWebView

- (void)initialLoad
{
	NSLog(@"initialLoad");
	
	NSURL* url = [[NSURL alloc] initFileURLWithPath:@"http://www.shi-gmbh.com/"];
	NSURLRequest* r = [NSURLRequest requestWithURL:url];
	[self loadRequest:r];
	[url release];
	
}

@end
