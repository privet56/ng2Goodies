#import "xmlparser.h"
#import "tools.h"

@implementation xmlparser

@synthesize m_xmlRoot;
@synthesize m_xmlCurrentItem;

- (id)init
{
	self = [super init];
	m_xmlRoot		= nil;
	m_xmlCurrentItem= nil;
	return self;
}
-(void)parse
{
	if(m_xmlRoot != nil)return;
	NSString* sXmlUrl = [tools getcfg:@"url"];
	NSXMLParser* parser = nil;
	if([tools isEmpty:sXmlUrl trim:YES])
	{
		sXmlUrl = [tools makeAbsPath:[tools getAppDir] withString:@"xml.xml"];
		if(![[NSFileManager defaultManager] fileExistsAtPath:sXmlUrl])
		{
			NSLog(@"fnf(xml):'%@'",sXmlUrl);
			return;
		}
		parser = [[NSXMLParser alloc] initWithData:[NSData dataWithContentsOfFile:sXmlUrl]];
	}
	else
	{
		NSLog(@"xmlurl:'%@'",sXmlUrl);
		//NSURL* urlXml = [NSURL URLWithString:[tools makeAbsPath:sXmlUrl withString:@"xml.xml"]];
		NSURL* urlXml = [NSURL URLWithString:sXmlUrl];
		parser = [[NSXMLParser alloc] initWithContentsOfURL:urlXml];		
	}
	
	[parser setShouldResolveExternalEntities:YES];
	[parser setDelegate:self];
	BOOL b = [parser parse];
	[parser release];
	if(b == NO)
	{
		NSLog(@"parse error(A:%p):%@",m_xmlRoot,sXmlUrl);
		return;
	}
    m_xmlCurrentItem = m_xmlRoot;
}
- (void)parser:(NSXMLParser*)parser parseErrorOccured:(NSError*)parseError
{
	NSLog(@"parse error(B):%@",[parseError localizedDescription]);
}
-(void)parser:(NSXMLParser*)parser didStartElement:(NSString*)elementName namespaceURI:(NSString*)namespaceURI qualifiedName:(NSString*)qName attributes:(NSDictionary*)attributeDict
{
	if(!elementName)return;
	xmlitem* parent				= m_xmlCurrentItem;
	m_xmlCurrentItem			= [[xmlitem alloc] init];
	m_xmlCurrentItem.m_parent	= parent;
	m_xmlCurrentItem.m_sEleName = [NSString stringWithString:elementName];
	[m_xmlCurrentItem.m_dAttributes addEntriesFromDictionary:attributeDict];
	if(parent == nil)
	{
		m_xmlRoot = m_xmlCurrentItem;
	}
	if(m_xmlCurrentItem.m_parent != nil)
	{
		NSMutableArray* a = m_xmlCurrentItem.m_parent.m_aiChildren;
		[a addObject:m_xmlCurrentItem];
	}
}
-(void)parser:(NSXMLParser*)parser didEndElement:(NSString*)elementName namespaceURI:(NSString*)namespaceURI qualifiedName:(NSString*)qName
{
	if(!elementName)return;
	if( m_xmlCurrentItem != nil)
		m_xmlCurrentItem = m_xmlCurrentItem.m_parent;
	if( m_xmlCurrentItem != nil)
	{
		//NSLog(@"%s sText:%@ parent:%d children:%d","didEndElement:",m_currentcolitem.m_sEleName,m_currentcolitem.m_parent,[m_currentcolitem.m_aiChildren count]);
	}
}
-(void)parser:(NSXMLParser*)parser foundCharacters:(NSString*)string
{
	if( m_xmlCurrentItem != nil)
	{
		m_xmlCurrentItem.m_sText = [NSString stringWithString:string];
		
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_uuml;" withString:@"ü"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_auml;" withString:@"ä"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_ouml;" withString:@"ö"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_Uuml;" withString:@"Ü"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_Auml;" withString:@"Ä"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_Ouml;" withString:@"Ö"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_para;" withString:@"§"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_sect;" withString:@"§"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_szlig;"withString:@"ß"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"_amp;"	withString:@"&"];
		m_xmlCurrentItem.m_sText = [m_xmlCurrentItem.m_sText stringByReplacingOccurrencesOfString:@"&amp;"	withString:@"&"];
	}
}

@end
