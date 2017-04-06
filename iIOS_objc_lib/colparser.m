#import "colparser.h"

@implementation colparser

@synthesize m_col;
@synthesize m_currentcolitem;

- (id)init
{
	self = [super init];
	
	m_col = nil;
	m_currentcolitem = nil;
	
	return self;
}

-(void)parse
{
	if(m_col != nil)return;
	NSString* sColUrl = [NSString stringWithFormat:@"%@/iPadVIEWER.app/%s",NSHomeDirectory(),"col.col"];
	if(![[NSFileManager defaultManager] fileExistsAtPath:sColUrl])
	{
		NSLog(@"fnf(col):'%@'",sColUrl);
		return;
	}
	
	//use this code if URL
	//NSURL* urlCol = [NSURL URLWithString:sColUrl];
	//NSXMLParser* parser = [[NSXMLParser alloc] initWithContentsOfURL:urlCol];
	
	NSXMLParser* parser = [[NSXMLParser alloc] initWithData:[NSData dataWithContentsOfFile:sColUrl]];
	[parser setShouldResolveExternalEntities:NO];
	[parser setDelegate:self];
	BOOL b = [parser parse];
	[parser release];
	if(b == NO)
	{
		NSLog(@"parse error(A:%p):%@",m_col,sColUrl);
		return;
	}
	com_shi_colitem* shiip = m_col;
	com_shi_colitem* col = [shiip getItemChild:0];
    m_currentcolitem = col;
}
- (void)parser:(NSXMLParser*)parser parseErrorOccured:(NSError*)parseError
{
	NSLog(@"parse error(B):%@",[parseError localizedDescription]);
}

-(void)parser:(NSXMLParser*)parser didStartElement:(NSString*)elementName namespaceURI:(NSString*)namespaceURI qualifiedName:(NSString*)qName attributes:(NSDictionary*)attributeDict
{
	if(!elementName)return;
	com_shi_colitem* parent		= m_currentcolitem;
	m_currentcolitem			= [[com_shi_colitem alloc] init];
	m_currentcolitem.m_parent	= parent;
	m_currentcolitem.m_sEleName = [NSString stringWithString:elementName];
	[m_currentcolitem.m_dAttributes addEntriesFromDictionary:attributeDict];
	if(parent == nil)
	{
		m_col = m_currentcolitem;
	}
	if(m_currentcolitem.m_parent != nil)
	{
		NSMutableArray* a = m_currentcolitem.m_parent.m_aiChildren;
		[a addObject:m_currentcolitem];		//NSLog(@"B:mychildren:%d a:%d",[a count],a);
	}
}
-(void)parser:(NSXMLParser*)parser didEndElement:(NSString*)elementName namespaceURI:(NSString*)namespaceURI qualifiedName:(NSString*)qName
{
	if(!elementName)return;
	if( m_currentcolitem != nil)
		m_currentcolitem = m_currentcolitem.m_parent;
	if( m_currentcolitem != nil)
	{
		//NSLog(@"%s sText:%@ parent:%d children:%d","didEndElement:",m_currentcolitem.m_sEleName,m_currentcolitem.m_parent,[m_currentcolitem.m_aiChildren count]);
	}
}
-(void)parser:(NSXMLParser*)parser foundCharacters:(NSString*)string
{
	if( m_currentcolitem != nil)
	{
		m_currentcolitem.m_sText = [NSString stringWithString:string];
		
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_uuml;" withString:@"ü"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_auml;" withString:@"ä"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_ouml;" withString:@"ö"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_Uuml;" withString:@"Ü"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_Auml;" withString:@"Ä"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_Ouml;" withString:@"Ö"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_para;" withString:@"§"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_sect;" withString:@"§"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_szlig;"withString:@"ß"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"_amp;"withString:@"&"];
		m_currentcolitem.m_sText = [m_currentcolitem.m_sText stringByReplacingOccurrencesOfString:@"&amp;"withString:@"&"];
	}
}

@end
