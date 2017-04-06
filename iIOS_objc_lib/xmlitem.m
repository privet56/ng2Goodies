#import "xmlitem.h"

@implementation xmlitem

@synthesize m_sEleName, m_sText,m_dAttributes, m_aiChildren, m_parent;

-(id)init
{
	m_sText			= [NSString stringWithString:@""];
	m_sEleName		= [NSString stringWithString:@""];
	m_dAttributes	= [[NSMutableDictionary alloc] init];
	m_aiChildren	= [[NSMutableArray alloc] init];
	m_parent		= nil;
	return self;
}

-(void)dealloc
{
	[self.m_sText release];
	[self.m_sEleName release];
	[self.m_dAttributes release];
	[self.m_aiChildren release];
	[self.m_parent release];
	[super dealloc];
}

-(int)getItemChildrenCount
{
	return [self.m_aiChildren count];
}
-(int)getItemChildrenCount:(NSString*)sFromType
{
	int iRe = 0;
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		xmlitem* item = [self.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:sFromType] == NSOrderedSame)
			iRe++;
	}
	return iRe;
}
-(xmlitem*)getItemChild:(int)iIdx
{
	return [self.m_aiChildren objectAtIndex:iIdx];
}
-(xmlitem*)getItemChild:(int)iIdx sFromType:(NSString*)sType
{
	int iRe = -1;
	for (int i = 0; i < [self.m_aiChildren count]; i++)
	{
		xmlitem* item = [self.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:sType] == NSOrderedSame)
		{
			iRe++;
			if(iRe == iIdx)return item;
		}
	}
	return nil;
}
-(BOOL)hasChildren
{
	return ([self getItemChildrenCount] > 0);
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
