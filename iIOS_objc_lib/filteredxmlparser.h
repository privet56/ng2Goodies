#import <Foundation/Foundation.h>
#import "xmlparser.h"

@interface filteredxmlparser : xmlparser
{
	IBOutlet NSString* m_sFilter;
}

@property (nonatomic, retain) NSString* m_sFilter;

-(xmlitem*) getCurrentItemChild:(int)i sFromType:(NSString*)type;
-(int) getCurrentItemChildrenCount:(NSString*)type;
-(BOOL) match:(xmlitem*)item;

@end
