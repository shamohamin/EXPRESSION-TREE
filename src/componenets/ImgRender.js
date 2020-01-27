import React from 'react'

const inlineCss = {
    margin : '20px' ,
    padding : '20px' ,
    boxshadow : '10px 10px 10px 10px solid black' ,
    width : '100%' ,

}



export const ImgRender = (props) => {
    return <div style={inlineCss}>
        <img src={require('../img/graph.jpg')} alt="graph" />

        <div className="text-center">
            <button className="btn btn-primary" 
                            onClick={() => props.history.push('/home')}>
                Back To Home
            </button>
        </div>
    </div>
}