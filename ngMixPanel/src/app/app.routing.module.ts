import {RouterModule, Routes} from "@angular/router";
import {NgModule} from "@angular/core";
import {DashboardComponent} from "./dashboard/dashboard.component";
import {SearchComponent} from "./search/search.component";

const appRoutes: Routes = [
  { path: "dashboard", component: DashboardComponent},
  { path: "search", component: SearchComponent },
  { path: "**", component: DashboardComponent}
];

@NgModule({
  imports: [
    RouterModule.forRoot(appRoutes)
  ],
  exports: [
    RouterModule
  ]
})
export class AppRoutingModule {

}
