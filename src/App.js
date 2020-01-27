import React from 'react';
import './App.css';
import "bootstrap/dist/css/bootstrap.css";
import { GetInput } from "./componenets/Getinput";
import { ImgRender } from './componenets/ImgRender'
import {BrowserRouter as Router , Route , Switch , Redirect , withRouter} 
        from 'react-router-dom' ;

const Img = withRouter(ImgRender) ;
const Input = withRouter(GetInput) ;

const selectComponenet = (routeProps) => {
  switch(routeProps.match.params.segment){
    case "home":
      return <Input />
    case "img":
      return <Img />
    default:
      return <Redirect to="/home" />
  }
}


function App() {
  return <Router>
    <Switch>
      <Route path="/:segment?" render={(routeProps) =>
                                      selectComponenet(routeProps)} />
      <Redirect to="/home" />
    </Switch>
  </Router>
  
}

export default App;
