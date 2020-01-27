const _ = require('lodash');
const exec = require('child_process').exec;

const controller = {

    getData : (req , res) => {
        const formula = _.pick(req.body , 'formula') ;
        console.log(req.body) ;
        console.log(formula.formula);
        exec('chmod u+x cpp_call.sh');
        const myShellScript = exec(`sh ./server/Controller/cpp_call.sh ${formula.formula}`);
        myShellScript.stdout.on('data', (data)=>{
            res.status(200).send({data : data}) ;
        });
        myShellScript.stderr.on('data', (data)=> {
            console.error(data);
            res.status(500).send(data) ;
        });
        
    }   
};


module.exports = controller ;