#import <Foundation/Foundation.h>
#import "xmlitem.h"


@interface xmlparser : NSObject <NSXMLParserDelegate>
{
	IBOutlet xmlitem* m_xmlRoot;
	IBOutlet xmlitem* m_xmlCurrentItem;
}

-(void)parse;

@property (nonatomic, assign) xmlitem* m_xmlRoot;
@property (nonatomic, assign) xmlitem* m_xmlCurrentItem;

@end
