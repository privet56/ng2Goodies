#import "filteredxmlparser.h"
#import "tools.h"

@implementation filteredxmlparser

@synthesize m_sFilter;

-(xmlitem*) getCurrentItemChild:(int)iIdx sFromType:(NSString*)type
{
	if([tools isEmpty:m_sFilter trim:YES])
		return [m_xmlCurrentItem getItemChild:iIdx sFromType:type];

	int iRe = -1;
	for (int i = 0; i < [m_xmlCurrentItem.m_aiChildren count]; i++)
	{
		xmlitem* item = [m_xmlCurrentItem.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:type] == NSOrderedSame)
		{
			if([self match:item])
				iRe++;
			if(iRe == iIdx)return item;
		}
	}
	return nil;	
}

-(int) getCurrentItemChildrenCount:(NSString*)type
{
	if([tools isEmpty:m_sFilter trim:YES])
		return [m_xmlCurrentItem getItemChildrenCount:type];
	
	int iRe = 0;
	for (int i = 0; i < [m_xmlCurrentItem.m_aiChildren count]; i++)
	{
		xmlitem* item = [m_xmlCurrentItem.m_aiChildren objectAtIndex:i];
		if([item.m_sEleName localizedCaseInsensitiveCompare:type] == NSOrderedSame)
		{
			if([self match:item])
				iRe++;
		}
	}
	return iRe;	
}

-(BOOL) match:(xmlitem*)item
{
	for (int i = 0; i < [item.m_aiChildren count]; i++)
	{
		xmlitem* childItem = [item.m_aiChildren objectAtIndex:i];
		NSRange r = [childItem.m_sText rangeOfString:m_sFilter options:NSCaseInsensitiveSearch];
		if(r.location != NSNotFound)return YES;
	}
	return NO;
}

@end
