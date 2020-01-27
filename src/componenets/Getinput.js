import React from 'react' ;
import '../Style/main.css';
import {sendRequest} from './sendRequest' ;
import $ from 'jquery';

export class GetInput extends React.Component {
    constructor(props){
        super(props) ;

        this.URL = "http://localhost:3600/api/formula" ;
        this.state = {
            formula : "" ,
            isSubmited : false ,
            error : "" ,
            response : ""
        };  
    }

    componentDidMount(){
        $('.button-submit').hover(function(){
            $(this).addClass("bg-primary")
        });
    }

    onSubmit = () => {
        sendRequest("post" , this.URL , this.state)
        .then(res => this.props.history.push('/img') ,
            this.setState({formula : "" , isSubmited : false ,
                                error : "" }))
        .catch(err => this.setState({error : err}))
    }
        

    makeStyle = () => <div className="card" id="main">
        <div className="card-header bg-info text-center" style={{borderRadius : '20px 20px 20px '}}>
            input the expression !!!!
        </div>
        <div className="card-body bg-transparent">
            <div className="alert-danger text-center">
                {this.state.error}
            </div>
            <label style={{marginLeft:'25px'}}>formula</label>
            <input className="form-control text-dark input-formula" value ={this.state.formula}
                        onChange={this.onChange} placeholder="Enter formula" autoFocus="on" />
            <button onClick={() => this.onSubmit()}
                    className="btn btn-primary mt-4 ml-4 bg-transparent text-dark float-left button-submit">
                submit
            </button>
        </div>
    </div>

    onChange = (event) => this.setState({formula : event.target.value}) ;

    render(){
        console.log(this.props)
        return <div className="main-template">
            <div>
                <div style={{margin : '20px'}}>
                    {this.makeStyle()}
                </div>
            </div>
        </div> 
    }



}

