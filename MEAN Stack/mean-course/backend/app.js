const express = require("express");
const path = require("path");
const bodyParser = require("body-parser");
const mongoose = require("mongoose");

const postRoutes = require("./routes/posts");

const app = express();


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ encoded: false }));
app.use("/images", express.static(path.join("backend/images")));

// MongoDB user: bryanjkline@gmail.com password: mongopassword
// user: bryan password: 5YUOhhHELoFMfoCt
mongoose.connect("mongodb+srv://bryan:5YUOhhHELoFMfoCt@cluster0-bdvbm.mongodb.net/node-angular?retryWrites=true&w=majority")
  .then(() => {
    console.log('Connected to DB');
  })
  .catch(() => {
    console.log('Connection failed');
  });

app.use((req, res, next) => {
  // setting headers to prevent CORS error which is set by default
  // for security
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  res.setHeader(
    "Access-Control-Allow-Methods",
    "GET, POST, PATCH, PUT, DELETE, OPTIONS"
  );
  next();
});

app.use("/api/posts", postRoutes);

module.exports = app;
