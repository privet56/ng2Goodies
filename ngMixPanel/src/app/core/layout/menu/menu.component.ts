import {IMenuItem, IMenuActionItem} from "./menu.interfaces";
import {Component} from "@angular/core";

@Component({
  selector: "ae-main-navigation",
  templateUrl: "./menu.component.html"
})
export class MenuComponent {

    public menuItems: Array<IMenuItem>;

    public actionItems: Array<IMenuActionItem>;

    constructor() {

        this.menuItems = [{
            title: "Dashboard",
            icon: "home",
            state: "dashboard"
        },{
          title: "Search",
          icon: "search",
          state: "search"
        }];

        this.actionItems = [{
            link: "https://wiki.redmedical.de/x/gIE4",
            icon1: "square",
            icon2: "phone",
            title: "Hilfe"
        }];

    }
}
