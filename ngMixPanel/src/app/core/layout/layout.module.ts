import {NgModule} from "@angular/core";
import {NavbarComponent} from "./navbar/navbar.component";
import {MenuComponent} from "./menu/menu.component";
import {AppRoutingModule} from "../../app.routing.module";
import {BrowserModule} from "@angular/platform-browser";

@NgModule({
  imports: [
    AppRoutingModule,
    BrowserModule
  ],
  declarations: [
    NavbarComponent,
    MenuComponent
  ],
  exports: [
    NavbarComponent,
    MenuComponent
  ]
})
export class LayoutModule {

}
