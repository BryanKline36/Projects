const mongoose = require('mongoose');

const postSchema = mongoose.Schema({
  title: { type: String, required: true },
  content: {type: String, required: true },
  imagePath: {type: String, required: true}
});

// Collection name will always be plural of name, here Posts from Post
module.exports = mongoose.model('Post', postSchema);
