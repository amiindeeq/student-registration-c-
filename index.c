using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace simple_progect
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            ShowData();
            ClearData();
        }
        SqlConnection con = new SqlConnection(@" Data Source=DESKTOP-30GDGQI;Initial Catalog=c; Integrated Security=True");

        private void ShowData()
        {
            con.Open();
            string Query = "select * from students";
            SqlDataAdapter sda = new SqlDataAdapter(Query, con);
            SqlCommandBuilder Builder = new SqlCommandBuilder(sda);
            var ds = new DataSet();
            sda.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
            con.Close();
        }
        private void ClearData()
        {
            txtStudentname.Clear();
            txtStudentTel.Clear();
            txtStudentAddress.Clear();
            cmbGender.SelectedIndex = -1;
            cmbDepertment.SelectedIndex = -1;
            cmbShifts.SelectedIndex = -1;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                con.Open();
                string select = "select * from students where StudID like'" +
               txtStudentid.Text + "%'or StudName like'" + txtStudentid.Text + "%'";
                SqlCommand cmd = new SqlCommand(select, con);
                SqlDataAdapter da = new SqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                da.Fill(dt);
                dataGridView1.DataSource = dt;
                con.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK,
               MessageBoxIcon.Error);
            }
            finally
            {
                con.Close();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void bntRegistration_Click(object sender, EventArgs e)
        {
            if (txtStudentname.Text == "" || txtStudentTel.Text == "" || txtStudentAddress.Text == "" || cmbGender.Text == "")
            {
                MessageBox.Show("Please Enter Missing Information", "Message", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                try
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Insert Into students values(@StudName,@StudTel,@Gender,@Addres,@Depertment,@date,@Shifts)", con);

                    cmd.Parameters.AddWithValue("@StudName", txtStudentname.Text);
                    cmd.Parameters.AddWithValue("@StudTel", txtStudentTel.Text);
                    cmd.Parameters.AddWithValue("@Gender", cmbGender.Text);
                    cmd.Parameters.AddWithValue("@Addres", txtStudentAddress.Text);
                    cmd.Parameters.AddWithValue("@Depertment", cmbDepertment.Text);
                    cmd.Parameters.AddWithValue("@date", dtp.Value);
                    cmd.Parameters.AddWithValue("@Shifts", cmbShifts.Text);
                    cmd.ExecuteNonQuery();
                    MessageBox.Show("Student Added Seccssesfuly.");
                    con.Close();
                    ShowData();
                    ClearData();


                }
                catch (Exception ex)
                {


                    MessageBox.Show(ex.Message);
                }

                finally { con.Close(); }
            }
        }
        int key = 0;
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            txtStudentid.Text = dataGridView1.SelectedRows[0].Cells[0].Value.ToString();
            txtStudentname.Text = dataGridView1.SelectedRows[0].Cells[1].Value.ToString();
            txtStudentTel.Text = dataGridView1.SelectedRows[0].Cells[2].Value.ToString();
            cmbGender.Text = dataGridView1.SelectedRows[0].Cells[3].Value.ToString();
            txtStudentAddress.Text = dataGridView1.SelectedRows[0].Cells[4].Value.ToString();
            cmbDepertment.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
            dtp.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
            cmbShifts.Text = dataGridView1.SelectedRows[0].Cells[5].Value.ToString();
            if (txtStudentname.Text == "")
            {
                key = 0;
            }
            else
            {
                key = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value.ToString());
            }

        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            if (txtStudentname.Text == "" || txtStudentTel.Text == "" || txtStudentAddress.Text == "" || cmbGender.Text == "")
            {
                MessageBox.Show("Please Enter Missing Information", "Message", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                try
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("update students set StudName=@StudName,StudTel=@StudTel,Gender=@Gender,Addres=@Addres,Depertment=@Depertment,date=@date,Shifts=@Shifts  WHERE StudID=@StudID ", con);
                    cmd.Parameters.AddWithValue("@StudName", txtStudentname.Text);
                    cmd.Parameters.AddWithValue("@StudTel", txtStudentTel.Text);
                    cmd.Parameters.AddWithValue("@Gender", cmbGender.Text);
                    cmd.Parameters.AddWithValue("@Addres", txtStudentAddress.Text);
                    cmd.Parameters.AddWithValue("@Depertment", cmbDepertment.Text);
                    cmd.Parameters.AddWithValue("@date", dtp.Value);
                    cmd.Parameters.AddWithValue("@Shifts", cmbShifts.Text);
                    cmd.Parameters.AddWithValue("@StudID", txtStudentid.Text);
                    cmd.ExecuteNonQuery();
                    MessageBox.Show("Student Updated Succssesfuly.");
                    con.Close();
                    ShowData();
                    ClearData();

                }
                catch (Exception ex)
                {


                    MessageBox.Show(ex.Message);
                }

                finally { con.Close(); }
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            if (txtStudentid.Text == "")
            {
                MessageBox.Show("Please Select Student");
            }
            else
            {
                try
                {
                    con.Open();
                    SqlCommand cmd = new SqlCommand("Delete From students where StudID=@StudID", con);
                    cmd.Parameters.AddWithValue("@StudID", txtStudentid.Text);
                    cmd.ExecuteNonQuery();
                    con.Close();
                    ClearData();
                    ShowData();
                    MessageBox.Show("Student Deleted Succesfully  ");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                finally { con.Close(); }
            }
        }
    }
}
