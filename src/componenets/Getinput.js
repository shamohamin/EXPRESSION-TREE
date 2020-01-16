import React from 'react' ;
import '../Style/main.css';

import $ from 'jquery';

export class GetInput extends React.Component {
    constructor(props){
        super(props) ;

        this.state = {
            formula : "" ,
            isSubmited : false 
        };  
    }

    componentDidMount(){
        $('.button-submit').hover(function(){
            $(this).addClass("bg-primary")
        });
    }

    makeStyle = () => <div className="card" id="main">
        <div className="card-header bg-info text-center" style={{borderRadius : '20px 20px 20px '}}>
            input the expression !!!!
        </div>
        <div className="card-body bg-transparent">
            <label style={{marginLeft:'25px'}}>formula</label>
            <input className="form-control text-dark input-formula" value ={this.state.formula}
                        onChange={this.onChange} placeholder="Enter formula" autoFocus="on" />
            <button className="btn btn-primary mt-4 ml-4 bg-transparent text-dark float-left button-submit">submit</button>
        </div>
    </div>

    onChange = (event) => this.setState({formula : event.target.value}) ;
    // onSubmit = () => 

    render(){
        return <div className="main-template">
            <div >
                <div style={{margin : '20px'}}>
                    {this.makeStyle()}
                </div>
            </div>
        </div> 
    }



}

