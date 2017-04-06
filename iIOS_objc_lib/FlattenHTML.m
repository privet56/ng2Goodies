#import "FlattenHTML.h"

#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/HTMLparser.h>


//add libxml2.2.x.dylib
//add header search paths: /usr/include/libxml2

@implementation NSString (FlattenHTML)

/*Callback function for stringByStrippingHTML*/
static void charactersParsed(void* context, const xmlChar* ch, int len)
{
  NSMutableString* result = context;
  NSString* parsedString;
  parsedString = [[NSString alloc] initWithBytesNoCopy:(xmlChar*) ch length: len encoding:NSUTF8StringEncoding freeWhenDone: NO];
  [result appendString: parsedString];
  [parsedString release];
}

/*GCS: custom error function to ignore errors */
static void structuredError(void* userData, xmlErrorPtr error)
{
   /* ignore all errors */
   (void)userData;
   (void)error;
}

/*Interpretes the receiver als HTML, removes all tags and returns the plain text*/
- (NSString*) flattenHTML
{
  int mem_base = xmlMemBlocks();
  NSMutableString* result = [NSMutableString string];
  xmlSAXHandler handler;
  bzero(&handler, sizeof(xmlSAXHandler));
  handler.characters = &charactersParsed;
  
  /* GCS: override structuredErrorFunc to mine so I can ignore errors */
  xmlSetStructuredErrorFunc(xmlGenericErrorContext, &structuredError);

  htmlSAXParseDoc((xmlChar*)[self UTF8String], "utf-8", &handler, result);
    
  if (mem_base != xmlMemBlocks())
  {
    NSLog( @"Leak of %d blocks found in htmlSAXParseDoc", xmlMemBlocks() - mem_base);
  }
  return result;
}

@end
