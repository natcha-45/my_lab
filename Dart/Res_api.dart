import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});
  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final formKey = GlobalKey<FormState>();
  late Future<List<dynamic>> _apigetusers;
  List<dynamic> _listUsers = [];
  bool _apiCalling = false;
  double font = 10;
  String ID = '';
  String Title = '';
  String Poststatus = '';

  Future<List<dynamic>> apiGetusers() async {
    String url = "https://jsonplaceholder.typicode.com/posts/";
    var uri = Uri.parse(url);
    var response = await http.get(uri);
    if (response.statusCode == 200 && response.body[0] == '[') {
      print("Request Success!");
      return jsonDecode(response.body) as List<dynamic>;
    } else if (response.statusCode == 200) {
      print("Request Success!");
      return jsonDecode('[' + response.body + ']') as List<dynamic>;
    } else {
      throw Exception("Request failed!! ${response.statusCode}");
    }
  }

  Future<void> apiPostUsers() async {
  String url = "https://jsonplaceholder.typicode.com/posts/";
  String Jsondata = '{' +
      '"userId": $ID,' +
      '"id": $ID,' +
      '"title": "$Title",' +
      '"body": "This is the body of my first post"' +
      '}';
  Map<String, String> headers = {
    'Content-Type': 'application/json',
  };

  var response = await http.post(
    Uri.parse(url),
    headers: headers,
    body: Jsondata,
  );

  if (response.statusCode == 201) {
    print("Post Success! ${response.statusCode}");
    setState(() {
      Poststatus = Jsondata;
    });
  } else {
    setState(() {
      Poststatus = "failed";
    });
    print("Post failed! ${response.statusCode}");
  }
}

  @override
  Widget build(BuildContext context) {
    if (!_apiCalling) {
      _apigetusers = apiGetusers();
      _apigetusers.then((value) {
        setState(() {
          _listUsers.addAll(value);
        });
      });
      _apiCalling = true;
    }
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: [
            Text('Get API',
                style: TextStyle(
                  fontSize: font,
                  color: Colors.black,
                  fontWeight: FontWeight.bold,
                )),
            Container(
              height: 200,
              width: 400,
              child: ListView.separated(
                itemCount: _listUsers.length,
                itemBuilder: (context, index) => ListTile(
                    title: Column(
                  children: [
                    Text('ID: ${_listUsers[index]["id"]}',
                        style: TextStyle(
                          fontSize: font,
                          color: Colors.black,
                          fontWeight: FontWeight.bold,
                        )),
                    Text('Title: ${_listUsers[index]["title"]}',
                        style: TextStyle(
                          fontSize: font,
                          color: Colors.black,
                          fontWeight: FontWeight.bold,
                        )),
                  ],
                )),
                separatorBuilder: (context, index) => Divider(
                  thickness: 2,
                  indent: 20,
                  endIndent: 20,
                  color: Colors.black,
                ),
              ),
            ),
            Text('Post API',
                style: TextStyle(
                  fontSize: font,
                  color: Colors.black,
                  fontWeight: FontWeight.bold,
                )),
            Container(
                child: Column(
                    mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                    children: [
                  Form(
                    key: formKey,
                    child: Column(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          Container(
                              height: 180,
                              width: 400,
                              child: Column(
                                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                                children: [
                                TextFormField(
                                  decoration: InputDecoration(
                                    labelText: 'Enter ID',
                                    labelStyle: TextStyle(
                                        fontSize: font,
                                        color: Colors.black,
                                        fontWeight: FontWeight.bold),
                                    filled: true,
                                    fillColor: Color.fromARGB(255, 110, 208, 238),
                                    focusedBorder: OutlineInputBorder(
                                      borderRadius: BorderRadius.circular(15),
                                    ),
                                  ),
                                  validator: (value) {
                                    if (value == null || value.isEmpty) {
                                      return 'Please enter ID';
                                    }
                                    if (!RegExp(r"^[0-9]+$").hasMatch(value)) {
                                      return 'Enter valid type';
                                    }
                                    return null;
                                  },
                                  onSaved: (value) {
                                    ID = value!;
                                  },
                                ),
                                TextFormField(
                                  decoration: InputDecoration(
                                    labelText: 'Enter Title',
                                    labelStyle: TextStyle(
                                        fontSize: font,
                                        color: Colors.black,
                                        fontWeight: FontWeight.bold),
                                    filled: true,
                                    fillColor: Color.fromARGB(255, 84, 185, 243),
                                    focusedBorder: OutlineInputBorder(
                                      borderRadius: BorderRadius.circular(15),
                                    ),
                                  ),
                                  validator: (value) {
                                    if (value == null || value.isEmpty) {
                                      return 'Please enter Title';
                                    }
                                    if (!RegExp(r"^[0-9a-zA-Z-]+$")
                                        .hasMatch(value)) {
                                      return 'Enter valid type';
                                    }
                                    return null;
                                  },
                                  onSaved: (value) {
                                    Title = value!;
                                  },
                                ),
                              ]))
                        ]),
                  ),
                ])),
            ElevatedButton(
                style: ElevatedButton.styleFrom(
                    backgroundColor: const Color.fromARGB(255, 255, 255, 255)),
                child: Text('Post',
                    style: TextStyle(
                        fontSize: font,
                        color: Colors.black,
                        fontWeight: FontWeight.bold)),
                onPressed: () {
                  if (formKey.currentState!.validate()) {
                    formKey.currentState!.save();
                    setState(() {
                      ID;
                      Title;
                      apiPostUsers();
                    });
                  }
                }),
                Container(
                  height: 100,
                  width: 400,
                  child: Column(
                    children: [
                      Text("Post body : ${Poststatus}"),
                    ]
                  )
                )
          ],
        ),
      ),
    );
  }
}
