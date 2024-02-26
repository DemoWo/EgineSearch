<h1>Search Engine</h1>

# What is a Search Engine?

Search Engine it's a console application, searching and having the ability to configure through files of the format JSON

# What's a stack of technologies used?

In the Search Engine project, we use the following list of the technologies:
<br>
[C++20](https://en.cppreference.com/w/cpp/20)
<br>
[CMake 3.22](https://cmake.org/cmake/help/latest/release/3.22.html)
<br>
[Nlohmann JSON](https://github.com/nlohmann/json)
<br>
[GoogleTest](https://github.com/google/googletest)

# How to build and run this project?

1. Build the project: <br>
`cmake -S . -B "build"`<br>
`cmake --build build --config Release`<br>

2. Copy files:<br>
`requests.json`, `config.json` and `resources` folder to the `Release` folder.

3. Run the application:<br>
`Release\SearchEngine.exe`<br>

# Files description:

<h3>config.json</h3>

```json
{
  "config": {
    "name": "SearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "./resources/file001.txt",
    "./resources/file002.txt",
    "./resources/file003.txt",
    "./resources/file004.txt"
  ]
}
```

config - general information.<br>
name - field with the name of the search engine.<br>
version - field with the version number of the search engine.<br>
max_responses - a field that determines the maximum number of responses to one request.<br>
files - contains the paths to the files to be searched. Inside the files list are the paths to the files.<br>

<h3>requests.json</h3>

```json
{
  "requests": [
    "banana",
    "seven",
    "counter",
    "dog"
  ]
}
```

requests - consists of a list of requests to be processed search engine.

<h3>answers.json</h3>

```json
{
    "answers": {
        "request001": {
            "relevance": [
                {
                    "docid": 0,
                    "rank": 1.0
                }
            ],
            "result": true
        },
        "request002": {
            "result": false
        },
        "request003": {
            "result": false
        },
        "request004": {
            "relevance": [
                {
                    "docid": 2,
                    "rank": 1.0
                }
            ],
            "result": true
        }
    }
}
```

answers - the base field in this file that contains the answers to queries.<br>
request - request001 ... 004 is the identifier of the request for which the response was generated.<br>
result - query search result.<br>
relevance - included in the answers.json file if this query was found more than one document.<br>
docid - the identifier of the document in which found the answer to the query.<br>
rank - search ranking.