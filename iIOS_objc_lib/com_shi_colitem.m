#import "com_shi_colitem.h"

@implementation com_shi_colitem

@synthesize m_sEleName, m_sText,m_sFN,m_sHitEnv, m_dAttributes, m_aiChildren, m_parent;

-(id)init
{
	m_sEleName		= [NSString stringWithString:@""];
	m_sText			= [NSString stringWithString:@""];
	m_sFN			= [NSString stringWithString:@""];
	m_sHitEnv		= [NSString stringWithString:@""];
	m_dAttributes	= [[NSMutableDictionary alloc] init];
	m_aiChildren	= [[NSMutableArray alloc] init];
	m_parent		= nil;
	return self;
}

-(void)dealloc
{
	[self.m_sText release];
	[self.m_sHitEnv release];
	[self.m_sEleName release];
	[self.m_dAttributes release];
	[self.m_aiChildren release];
	[self.m_parent release];
	[super dealloc];
}

-(int)getItemChildrenCount
{
	int iRe = 0;
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		com_shi_colitem* item = [self.m_aiChildren objectAtIndex:i];
		if( ([item.m_sEleName localizedCaseInsensitiveCompare:@"ITEM"] == NSOrderedSame) ||
			([item.m_sEleName localizedCaseInsensitiveCompare:@"COL"] == NSOrderedSame))
			iRe++;
	}
	return iRe;
}
-(com_shi_colitem*)getItemChild:(int)iIdx
{
	int iRe = -1;
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		com_shi_colitem* item = [self.m_aiChildren objectAtIndex:i];
		if( ([item.m_sEleName localizedCaseInsensitiveCompare:@"ITEM"] == NSOrderedSame) ||
			([item.m_sEleName localizedCaseInsensitiveCompare:@"COL"] == NSOrderedSame))
		{
			iRe++;
			if(iRe == iIdx)
			{
				return item;
			}
		}
		
	}
	return nil;
}
-(com_shi_colitem*)getItemDoc:(int)iIdx
{
	int iRe = -1;
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		com_shi_colitem* item = [self.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:@"DOC"] == NSOrderedSame)
		{
			iRe++;
			if(iRe == iIdx)
			{
				return item;
			}
		}
		
	}
	return nil;
}
-(BOOL)hasChildren
{
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		com_shi_colitem* item = [self.m_aiChildren objectAtIndex:i];
		if( ([item.m_sEleName localizedCaseInsensitiveCompare:@"ITEM"] == NSOrderedSame) ||
		   ([item.m_sEleName localizedCaseInsensitiveCompare:@"COL"] == NSOrderedSame))
		{
			return YES;
		}
	}
	return NO;
}
-(BOOL)hasDocs
{
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		com_shi_colitem* item = [self.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:@"DOC"] == NSOrderedSame)
		{
			return YES;
		}
	}
	return NO;
}
-(NSString*)getTitle
{
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		com_shi_colitem* item = [self.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:@"TITLE"] == NSOrderedSame)
			return item.m_sText;
	}
	return @"";
}
-(NSString*)getAttr:(NSString*)sAttrName
{
	NSString* sAttrVal = [self.m_dAttributes objectForKey:[sAttrName lowercaseString]];
	if(sAttrVal != nil)return sAttrVal;
	sAttrVal = [self.m_dAttributes objectForKey:[sAttrName uppercaseString]];
	if(sAttrVal != nil)return sAttrVal;
	sAttrVal = [self.m_dAttributes objectForKey:sAttrName];
	if(sAttrVal != nil)return sAttrVal;
	
	NSArray* keys = [self.m_dAttributes allKeys];
	for(int i=0; i < [keys count]; i++)
	{
		NSString* key = [keys objectAtIndex:i];
		if([key localizedCaseInsensitiveCompare:sAttrName] == NSOrderedSame)
		{
			NSString* val = [self.m_dAttributes objectForKey:key];
			if(val != nil)
				return val;
		}
		//NSLog(@"getAttr:  ATTR(%d):'%@'='%@'", i,key,val);		
	}
	//NSLog(@"getAttr:END: '%@'=='%@'=='%@' ==>> %@", sAttrName, [sAttrName lowercaseString],[sAttrName uppercaseString], sAttrVal);
	return @"";
} 

@end
