import React from 'react' ;
import '../Style/main.css';
import {sendRequest} from './sendRequest' ;
import $ from 'jquery';
import { validate } from "./validate";

export class GetInput extends React.Component {
    constructor(props){
        super(props) ;

        this.URL = "http://localhost:3600/api/formula" ;
        this.state = {
            formula : "" ,
            isSubmited : false ,
            error : "" ,
            response : "" ,
            errors : {} ,
            rules : {
                formula : {
                    empty : true ,
                    num_and_op : true
                }
            }
        };
         
    }

    componentDidMount(){
        $('.button-submit').hover(function(){
            $(this).addClass("bg-primary")
        });
    }

    get isValidForSubmit(){
        return this.state.errors.formula.length === 0 ;
    }

    onSubmit = () => {

        if(this.isValidForSubmit){
            sendRequest("post" , this.URL , this.state )
            .then(res => this.setState({response : res.data.msg , error : ''}))
            .catch(err => {
                console.log(err)
                this.setState({error : err , response : ''})
            })
        }else{
            this.setState({error : "payattention to rules please !!!" ,  response : ''})
        }
    }
        


    static getDerivedStateFromProps(props , state){
        return {
            errors : validate(state.rules , state)
        }
    } 

    makeStyle = () => <div className="card" style={{margin:'10%'}}>
        <div className="card-header bg-info text-center" style={{borderRadius : '20px 20px 20px '}}>
            input the expression !!!!
        </div>
        <div className="card-body bg-transparent">
            <div className={this.state.response.length !== 0 ? `alert-success text-center` : `alert-danger text-center`}>
                {
                    this.state.response.length !== 0 ? this.state.response : this.state.error
                }
            </div>
            <div>
                <label style={{marginLeft:'25px'}}>formula</label>
                <input className="form-control text-dark input-formula" value ={this.state.formula}
                            onChange={this.onChange} placeholder="Enter formula" autoFocus="on" />
                <div className="p-3">
                    {
                        this.state.errors.formula.map(err => <div key={err} className="alert alert-danger m-2 p-2 text-white span">
                            {err}
                        </div>)
                    }
                </div>
            </div>
            <button onClick={() => this.onSubmit()}
                    className="btn btn-primary ml-4 bg-transparent text-dark float-left button-submit">
                submit
            </button>
        </div>
    </div>

    onChange = (event) => this.setState({formula : event.target.value.trim()}) ;

    render(){
        console.log(this.state)
        return <div className="main-template">
            <div>
                <div style={{margin : '20px'}}>
                    {this.makeStyle()}
                </div>
            </div>
        </div> 
    }



}

