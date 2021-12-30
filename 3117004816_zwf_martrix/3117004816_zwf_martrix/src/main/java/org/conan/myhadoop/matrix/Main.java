package org.conan.myhadoop.matrix;

import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;

import org.apache.hadoop.mapred.JobConf;

public class Main {

    public static final String HDFS = "hdfs://localhost:9000";
    public static final Pattern DELIMITER = Pattern.compile("[\t,]");

    public static void main(String[] args) {
 //       matrixMultiply();
        sparseMatrixMultiply();
    }
    
    public static void matrixMultiply() {
        Map<String, String> path = new HashMap<String, String>();
        path.put("m1", "F:/3117004816_zwf_martrix/3117004816_zwf_martrix/logfile/matrix/matrix1.csv");// 本地的数据文件
        path.put("m2", "F:/3117004816_zwf_martrix/3117004816_zwf_martrix/logfile/matrix/matrix2.csv");
        path.put("input", HDFS + "/user/hdfs/matrix");// HDFS的目录
        path.put("input1", HDFS + "/user/hdfs/matrix/m1");
        path.put("input2", HDFS + "/user/hdfs/matrix/m2");
        path.put("output", HDFS + "/user/hdfs/matrix/output");

        try {
            MatrixMultiply.run(path);// 启动程序
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.exit(0);
    }
    
    public static void sparseMatrixMultiply() {
        Map<String, String> path = new HashMap<String, String>();
        path.put("m1", "F:/3117004816_zwf_martrix/3117004816_zwf_martrix/logfile/matrix/sparsematrix1.csv");// 本地的数据文件
        path.put("m2", "F:/3117004816_zwf_martrix/3117004816_zwf_martrix/logfile/matrix/sparsematrix2.csv");
        path.put("input", HDFS + "/user/hdfs/matrix");// HDFS的目录
        path.put("input1", HDFS + "/user/hdfs/matrix/m1");
        path.put("input2", HDFS + "/user/hdfs/matrix/m2");
        path.put("output", HDFS + "/user/hdfs/matrix/output");

        try {
            SparseMatrixMultiply.run(path);// 启动程序
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.exit(0);
    }

    public static JobConf config() {// Hadoop集群的远程配置信息
        JobConf conf = new JobConf(Main.class);
        conf.setJobName("MartrixMultiply");
        conf.addResource("classpath:/hadoop/core-site.xml");
        conf.addResource("classpath:/hadoop/hdfs-site.xml");
        conf.addResource("classpath:/hadoop/mapred-site.xml");
        return conf;
    }

}
