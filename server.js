const express = require('express') ;
const app = express() ;
const bodyParser = require('body-parser') ;
const cors = require('cors');
const router = express.Router();
app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended : true}));
app.use('/' , router) ;
const api = require('./server/Routes/api.route');
router.use('/api' , api) ;

app.listen('3600' , () => console.log("connection successful !!"));