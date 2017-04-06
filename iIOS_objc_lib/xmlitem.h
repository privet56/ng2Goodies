#import <Foundation/Foundation.h>

@interface xmlitem : NSObject
{
	IBOutlet NSMutableDictionary* m_dAttributes;
	IBOutlet NSString* m_sEleName;
	IBOutlet NSString* m_sText;
	IBOutlet xmlitem* m_parent;
	IBOutlet NSMutableArray* m_aiChildren;
}

-(id)init;
-(BOOL)hasChildren;
-(int)getItemChildrenCount;
-(int)getItemChildrenCount:(NSString*)sFromType;
-(NSString*)getAttr:(NSString*)sAttrName;
-(xmlitem*)getItemChild:(int)iIdx;
-(xmlitem*)getItemChild:(int)iIdx sFromType:(NSString*)sType;

@property (nonatomic, retain) NSMutableDictionary* m_dAttributes;
@property (nonatomic, retain) NSString* m_sText;
@property (nonatomic, retain) NSString* m_sEleName;
@property (nonatomic, retain) NSMutableArray* m_aiChildren;
@property (nonatomic, retain) xmlitem* m_parent;

@end
