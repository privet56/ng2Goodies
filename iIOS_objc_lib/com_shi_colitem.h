#import <Foundation/Foundation.h>

@interface com_shi_colitem : NSObject
{
	IBOutlet NSString* m_sEleName;
	IBOutlet NSMutableDictionary* m_dAttributes;
	IBOutlet NSString* m_sText;
	IBOutlet NSString* m_sFN;
	IBOutlet NSMutableArray* m_aiChildren;
	IBOutlet com_shi_colitem* m_parent;
	IBOutlet NSString* m_sHitEnv;
}

-(id)init;
-(NSString*)getTitle;
-(int)getItemChildrenCount;
-(com_shi_colitem*)getItemChild:(int)iIdx;
-(BOOL)hasChildren;
-(BOOL)hasDocs;
-(com_shi_colitem*)getItemDoc:(int)iIdx;
-(NSString*)getAttr:(NSString*)sAttrName;

@property (nonatomic, retain) NSString* m_sEleName;
@property (nonatomic, retain) NSMutableDictionary* m_dAttributes;
@property (nonatomic, retain) NSString* m_sText;
@property (nonatomic, retain) NSString* m_sFN;
@property (nonatomic, retain) NSString* m_sHitEnv;
@property (nonatomic, retain) NSMutableArray* m_aiChildren;
@property (nonatomic, retain) com_shi_colitem* m_parent;

@end
