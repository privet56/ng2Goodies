#import "tools.h"

@implementation tools

+(NSString*)getcfg:(NSString*)sEntryName
{
	NSString* sEntryValue = [[[NSBundle mainBundle]infoDictionary]objectForKey:sEntryName];
	if(sEntryValue == nil)
	{
		NSLog(@"getcfg\tERR:sEntryName.nf:'%@'",sEntryName);
		return @"";
	}
	if([sEntryValue length] < 1)
	{
		NSLog(@"getcfg\tERR:sEntryName.empty:'%@'",sEntryName);
	}
	
	sEntryValue = [sEntryValue stringByReplacingOccurrencesOfString:@"\\n" withString:@"\n"];
	
	return sEntryValue;
}

+(void)printviews:(UIView*)v rec:(int)iRec
{
	for(UIView* view in [v subviews])
	{
		NSString* s = [@"" stringByPaddingToLength:(iRec*2) withString:@"." startingAtIndex:0];
		NSLog(@"%@%@",s,[[view class]description]/*,view*/);
		[tools printviews:view rec:(iRec+1)];
	}
}

+(NSString*)getAppDir
{
	{
		return [[NSBundle mainBundle] bundlePath];
	}
	/*
	static NSString* sAppDir = nil;
	if(sAppDir != nil)
		return sAppDir;
	
	NSFileManager* fm = [NSFileManager defaultManager];
	NSArray* subs = [fm directoryContentsAtPath:NSHomeDirectory()];
	NSArray* subapps = [subs filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self ENDSWITH '.app'"]];
	if([subapps count] != 1)
	{
		NSLog(@"getAppDir ERR:!.app");
		return sAppDir;
	}
	sAppDir = [NSString stringWithFormat:@"%@/%@",NSHomeDirectory(),[subapps objectAtIndex:0]];
	return sAppDir;
	*/
}

+(BOOL)startsWidth:(NSString*)s withString:(NSString*)sString
{
	if([tools isEmpty:s trim:YES])return NO;
	if([tools isEmpty:sString trim:YES])return NO;
	
	NSRange r = [s rangeOfString:sString];
	if((r.location != NSNotFound) && (r.location == 0))
		return YES;
	
	return NO;
}

+(NSString*)removeBetween:(NSString*)s firstString:(NSString*)s1 secondString:(NSString*)s2
{
	NSScanner* scanner	= [NSScanner scannerWithString:s];
	NSString* sText		= nil;
	
	while(![scanner isAtEnd])
	{
		[scanner scanUpToString:s1 intoString:nil];
		[scanner scanUpToString:s2 intoString:&sText];
		s = [s stringByReplacingOccurrencesOfString:[NSString stringWithFormat:@"%@%@",sText,s2] withString:@" "];
	}
	
	return [s stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
}

+(BOOL)isAbs:(NSString*)s
{
	if([tools isEmpty:s trim:YES])return NO;
	
	if([s characterAtIndex:0] == '/')
		return YES;
	
	NSRange r = [s rangeOfString:@"http:"];
	if((r.location != NSNotFound) && (r.location == 0))
		return YES;
	
	r = [s rangeOfString:@"https:"];
	if((r.location != NSNotFound) && (r.location == 0))
		return YES;
	
	return NO;
}

+(BOOL)isEmpty:(NSString*)s trim:(BOOL)trim
{
	if(s == nil)return YES;
	if([s length] < 1)return YES;
	if(trim && ([[s stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]] length] < 1))return YES;
	return NO;
}

+(NSString*)makeAbsPath:(NSString*)s1 withString:(NSString*)s2
{
	BOOL b1 = [tools isEmpty:s1 trim:YES];
	BOOL b2 = [tools isEmpty:s2 trim:YES];
	if(b1 && b2)return @"";
	
	if(!b1)s1 = [s1 stringByReplacingOccurrencesOfString:@"\\" withString:@"/"];
	if(!b2)s2 = [s2 stringByReplacingOccurrencesOfString:@"\\" withString:@"/"];
	
	if(b1)return s2;
	if(b2)return s1;

	if([tools isAbs:s2])return s2;
	
	b1 = [s1 characterAtIndex:([s1 length]-1)] == '/';
	b2 = [s2 characterAtIndex:0] == '/';
	
	if(!b1 && !b2)
	{
		return [NSString stringWithFormat:@"%@/%@",s1,s2];
	}
	if(b1 && b2)
	{
		return [NSString stringWithFormat:@"%@%@",s1,[s2 substringFromIndex:1]];
	}
	
	return [NSString stringWithFormat:@"%@%@",s1,s2];
}

@end
