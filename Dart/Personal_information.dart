// Copyright (c) 2019, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme:
            ColorScheme.fromSeed(seedColor: Colors.lightGreen.shade100),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Lab 8'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  final String title;

  const MyHomePage({
    super.key,
    required this.title,
  }) : super();

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final formKey = GlobalKey<FormState>();
  double font = 11;
  double icon_size = 18;
  double re_size = 5;
  double scales = 0.7;
  List<String> name = [];
  List<String> birthday = [];
  List<String> phonenumber = [];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          children: [
            Container(
              width: 400,
              height: 400,
              decoration: BoxDecoration(
                border: Border.all(
                  color: Colors.yellow.shade900,
                  width: 3.0,
                ),
                borderRadius: BorderRadius.circular(15),
              ),
              child: Column(
                  mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                  children: [
                    Container(
                        width: 300,
                        height: 30,
                        decoration: BoxDecoration(
                          color: Colors.lightGreen.shade300,
                          borderRadius: BorderRadius.circular(5),
                        ),
                        child: Column(
                            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                            children: [
                              Text('Please enter personal information.',
                                  style: TextStyle(
                                    fontSize: 15,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                            ])),
                    Form(
                        key: formKey,
                        child: Column(children: [
                          Container(
                              width: 350,
                              height: 250,
                              child: Column(
                                  mainAxisAlignment:
                                      MainAxisAlignment.spaceEvenly,
                                  children: [
                                    TextFormField(
                                      decoration: InputDecoration(
                                        prefixIcon:
                                            Icon(Icons.person, size: icon_size),
                                        labelText: 'Enter name and Lastname',
                                        labelStyle: TextStyle(
                                            fontSize: font,
                                            color: Colors.black,
                                            fontWeight: FontWeight.bold),
                                        filled: true,
                                        fillColor: Colors.green.shade100,
                                        focusedBorder: OutlineInputBorder(
                                          borderRadius:
                                              BorderRadius.circular(15),
                                        ),
                                      ),
                                      validator: (value) {
                                        if (value == null || value.isEmpty) {
                                          return 'กรุณากรอก ชื่อ และ นามสกุล';
                                        }
                                        if (!RegExp(
                                                r'^[ก-๙a-zA-Z]+[ ]+[ก-๙a-zA-Z]+$')
                                            .hasMatch(value)) {
                                          return 'กรอกชื่อ ชื่อ นามสกุล ไม่ถูกต้อง';
                                        }
                                        return null;
                                      },
                                      onSaved: (value) {
                                        name += [value!];
                                      },
                                    ), //end name and lastname
                                    TextFormField(
                                      decoration: InputDecoration(
                                        prefixIcon:
                                            Icon(Icons.cake, size: icon_size),
                                        hintText: 'dd/mm/yyyy',
                                        hintStyle: TextStyle(
                                            fontSize: font,
                                            color: Colors.black,
                                            fontWeight: FontWeight.bold),
                                        labelText: 'Birthday',
                                        labelStyle: TextStyle(
                                            fontSize: font,
                                            color: Colors.black,
                                            fontWeight: FontWeight.bold),
                                        filled: true,
                                        fillColor: Colors.green.shade100,
                                        focusedBorder: OutlineInputBorder(
                                          borderRadius:
                                              BorderRadius.circular(15),
                                        ),
                                      ),
                                      validator: (value) {
                                        if (value == null || value.isEmpty) {
                                          return 'กรุณากรอก วัน เดือน ปี เกิด';
                                        }
                                        if (!RegExp(
                                                r'^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4}$')
                                            .hasMatch(value)) {
                                          return 'รูปแบบ วัน เดือน ปี เกิด ไม่ถูกต้อง';
                                        }
                                        return null;
                                      },
                                      onSaved: (value) {
                                        birthday += [value!];
                                      },
                                    ), //end phonenumber
                                    TextFormField(
                                      decoration: InputDecoration(
                                        prefixIcon:
                                            Icon(Icons.phone, size: icon_size),
                                        labelText: 'Phone number',
                                        labelStyle: TextStyle(
                                            fontSize: font,
                                            color: Colors.black,
                                            fontWeight: FontWeight.bold),
                                        filled: true,
                                        fillColor: Colors.green.shade100,
                                        focusedBorder: OutlineInputBorder(
                                          borderRadius:
                                              BorderRadius.circular(15),
                                        ),
                                      ),
                                      validator: (value) {
                                        if (value == null || value.isEmpty) {
                                          return 'กรุณากรอก เบอร์โทรศัพท์';
                                        }
                                        if (!RegExp(r"^[0][1-9][0-9]{8}")
                                            .hasMatch(value)) {
                                          return 'รูปแบบ เบอร์โทรศัพท์ ไม่ถูกต้อง';
                                        }
                                        return null;
                                      },
                                      onSaved: (value) {
                                        phonenumber += [value!];
                                      },
                                    ), //end phonenumber
                                  ])),
                        ])),
                    Row(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          ElevatedButton(
                              style: ElevatedButton.styleFrom(
                                  backgroundColor: Colors.green.shade200),
                              child: Text('Save',
                                  style: TextStyle(
                                      fontSize: font,
                                      color: Colors.black,
                                      fontWeight: FontWeight.bold)),
                              onPressed: () {
                                if (formKey.currentState!.validate()) {
                                  formKey.currentState!.save();
                                  showDialog(
                                    context: context,
                                    builder: (BuildContext context) {
                                      return AlertDialog(
                                        title: Text(
                                          'Save success!!',
                                          style: TextStyle(
                                              fontSize: 12,
                                              color: Colors.black,
                                              fontWeight: FontWeight.bold),
                                        ),
                                        actions: <Widget>[
                                          TextButton(
                                            onPressed: () {
                                              Navigator.pop(
                                                context,
                                                'OK',
                                              );
                                            },
                                            child: Text(
                                              'OK',
                                              style: TextStyle(
                                                  fontSize: 12,
                                                  fontWeight: FontWeight.bold),
                                            ),
                                          ),
                                        ],
                                      );
                                    },
                                  );
                                  setState(() {});
                                }
                              }),
                          ElevatedButton(
                              style: ElevatedButton.styleFrom(
                                  backgroundColor: Colors.green.shade200),
                              child: Text('Reset',
                                  style: TextStyle(
                                      fontSize: font,
                                      color: Colors.black,
                                      fontWeight: FontWeight.bold)),
                              onPressed: () {
                                setState(() {
                                  name = [];
                                  birthday = [];
                                  phonenumber = [];
                                });
                              }),
                        ])
                  ]),
            ),
            Container(
                width: 400,
                height: 300,
                decoration: BoxDecoration(
                  border: Border.all(
                    color: Colors.yellow.shade800,
                    width: 3.0,
                  ),
                  borderRadius: BorderRadius.circular(15),
                ),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                  children: [
                    Container(
                        width: 300,
                        height: 30,
                        decoration: BoxDecoration(
                          color: Colors.lightGreen.shade300,
                          borderRadius: BorderRadius.circular(5),
                        ),
                        child: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              Text('Show information',
                                  style: TextStyle(
                                    fontSize: 15,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                            ])),
                    Container(
                      width: 300,
                      height: 150,
                      decoration: BoxDecoration(
                        borderRadius: BorderRadius.circular(5),
                      ),
                      child: ListView.separated(
                        itemCount: name.length,
                        itemBuilder: (context, index) => ListTile(
                          title: Column(children: [
                            Row(children: [
                              Text('Person: ',
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                              Text( '$index',
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                              Text('   Name: ',
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                              Text(name[index],
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                            ]),
                            Row(children: [
                              Text('Birthday',
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                              Text(birthday[index],
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                              Text('   Phone:',
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                              Text(phonenumber[index],
                                  style: TextStyle(
                                    fontSize: font,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                  )),
                            ]),
                          ]),
                        ),
                        separatorBuilder: (context, index) => Divider(
                          thickness: 2,
                          indent: 20,
                          endIndent: 20,
                          color: Colors.black,
                        ),
                      ),
                    ),
                  ],
                )),
          ],
        ),
      ),
    );
  }
}
