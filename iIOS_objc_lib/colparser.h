//
//  colparser.h
//  iPadVIEWER
//
//  Created by Peter Spiske on 31.08.10.
//  Copyright 2010 com.shi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "com_shi_colitem.h"


@interface colparser : NSObject
{
	IBOutlet com_shi_colitem* m_col;
	IBOutlet com_shi_colitem* m_currentcolitem;
}

-(void)parse;

@property (nonatomic, assign) com_shi_colitem* m_col;
@property (nonatomic, assign) com_shi_colitem* m_currentcolitem;

@end
