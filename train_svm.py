from sklearn import svm
import csv

class dp_svm:
    def __init__(self):
        self.model = svm.SVR(gamma='auto')
        self.data = -1
        self.x = -1
        self.y = -1
    def get_data(self,filename):
        with open(filename) as f:
            csv_reader = csv.reader(f,delimiter=',')
            self.data = []
            for row in csv_reader:
                self.data.append(list(map(float,row)))
            # print(data)

    def get_x_y(self):
        if(self.data==-1):
            self.load()
            return
        self.x = [row[:-1] for row in self.data]
        self.y = [row[-1:] for row in self.data]
        flat_list = []
        for sublist in self.y:
            for item in sublist:
                flat_list.append(item)
        self.y = flat_list
        # return (x,flat_list)

    def train_model(self):
        if(self.x==-1):
            self.get_x_y()
        self.model.fit(self.x,self.y)

    def predict_model(self,X):
        return self.model.predict(X)
    def load(self,filename='test_runs/sample.csv'):
        self.get_data(filename)
        self.get_x_y()
    def get_x(self):
        return self.x
    def get_y(self):
        return self.y

if __name__=='__main__':
    obj1 = dp_svm()
    obj1.load()
    obj1.train_model()
    x = obj1.get_x()
    result = obj1.predict_model([x[0]])
    print(result)