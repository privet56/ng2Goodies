#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
//#import <Cocoa/Cocoa.h>
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


#define VIEW_NONE 0
#define VIEW_TREE 1
#define VIEW_SEARCH 2
#define VIEW_BOOKMARKS 3


@interface tools : NSObject
{

}

+(NSString*)getcfg:(NSString*)sEntryName;
+(void)printviews:(UIView*)v rec:(int)iRec;
+(NSString*)getAppDir;
+(BOOL)isEmpty:(NSString*)s trim:(BOOL)trim;
+(NSString*)makeAbsPath:(NSString*)s1 withString:(NSString*)s2;
+(BOOL)isAbs:(NSString*)s;
+(BOOL)startsWidth:(NSString*)s withString:(NSString*)sString;
+(NSString*)removeBetween:(NSString*)s firstString:(NSString*)s1 secondString:(NSString*)s2;

@end
