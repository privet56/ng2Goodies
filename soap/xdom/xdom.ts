
export const namespaceSeparator: string = ':';

export const nodeTypeNames: string[] = [
    undefined,
    "Element",
    "Attribute",
    "Text",
    "CDATA Section",
    "Entity Reference",
    "Entity",
    "Processing Instruction",
    "Comment",
    "Document",
    "Document Type",
    "Document Fragment",
    "Notation"
];

export enum nodeTypes {
    UNDEFINED = 0,
    ELEMENT = 1,
    ATTRIBUTE = 2,
    TEXT = 3,
    CDATA_SECTION = 4,
    ENTITY_REFERENCE = 5,
    ENTITY = 6,
    PROCESSING_INSTRUCTION = 7,
    COMMENT = 8,
    DOCUMENT = 9,
    DOCUMENT_TYPE = 10,
    DOCUMENT_FRAGMENT = 11,
    NOTATION = 12
}

export const nodeTypeKeys: string[] = Object.keys(nodeTypes);

export class XDom
{
    public static isNodeType(nodeType: number): boolean {
        return null === nodeType || undefined === nodeType ? false : undefined !== nodeTypeKeys[nodeType];
    }

    public static isNodeTypeKey(nodeTypeKey: any): boolean {
        return null === nodeTypeKey || undefined === nodeTypeKey ? false : undefined !== nodeTypes[nodeTypeKey];
    }

    public static nodeType(nodeTypeKey: any): string {
        return null === nodeTypeKey || undefined === nodeTypeKey ? undefined : nodeTypes[nodeTypeKey];
    }

    public static nodeTypeKey(nodeType: number): string {
        return null === nodeType || undefined === nodeType ? undefined : nodeTypeKeys[nodeType];
    }

    public static nodeTypeName(nodeType: number): string {
        return null === nodeType || undefined === nodeType ? undefined : nodeTypeNames[nodeType];
    }
}
