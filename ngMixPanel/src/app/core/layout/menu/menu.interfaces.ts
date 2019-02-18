export interface IMenuItem {

    /**
     * Title of the menu items. Used as name in menu
     */
    title: string;

    /**
     * Font-Awesome icon (without 'fa-')
     * Displayed left to the title
     */
    icon: string;

    /**
     * State to be opened when the user clicks on the menu entry
     * Neccessary if a menu item has no children (item attribute) and createModalModelName is not defined.
     */
    state: string;

}

interface IAbstractMenuItem {
    title: string;
}

export interface IMenuActionItem extends IAbstractMenuItem {
    link: string;
    icon1: string;
    icon2: string;
}
